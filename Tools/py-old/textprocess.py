import os, sys, re

def show_exception_and_exit(exc_type, exc_value, tb):
	import traceback
	
	traceback.print_exception(exc_type, exc_value, tb)
	sys.exit(-1)

def getEntries(textList):
	"""takes a compiled file and returns a list of individual text entries"""
	
	result = []

	entry = ""
	textID = ""
	definition = None

	newEntry = True
	lineIndex = 0

	for line in textList.splitlines():
		l = line.strip()
		lineIndex += 1

		if newEntry: # new text entry
			if l == "":
				next # Skip empty lines
			
			else:
				matchobj = re.match(r"^#\s*([0x[0-9a-fA-F]+|#)\s*(\w+)?$", l, re.M | re.I)
				
				assert matchobj, "Error at line " + str(lineIndex) + ' - "' + l + '":\nEntries must begin with the format "#0xtextID optional_definition" or "## optional_definition"'
				
				if matchobj.group(1) == '#': # if no ID given, use the previous one + 1
					textID = hex(int(textID, 16)+1)
				else:
					textID = matchobj.group(1)
				
				definition = matchobj.group(2)
				newEntry = False
		
		elif l[-3:] == "[X]": # Line ends in [X] (end of text entry)
			entry += (line + "\n")
			tmp = (entry, textID, definition)
			result.append(tmp)
			entry = ""
			definition = None
			newEntry = True
		
		else:
			entry += (line + "\n")

	return result

# more like preprocess but ok
def assemble(filepath, depth = 0):
	if depth > 500:
		print("Warning: #include depth exceeds 500. Check for circular inclusion.\nCurrent file: " + filepath)
		return None
	
	result = ""

	with open(filepath, 'r') as f:
		lines = f.readlines() # each line is added to the list
	
	for line in lines:
		matchobj = re.match(r"^#include\s+(.+)", line.strip(),re.M|re.I)
		
		if matchobj:
			includee = matchobj.group(1).strip()
			
			if (includee[0] == '"'):
				includee = includee.strip('"')
			
			dirpath = os.path.dirname(filepath)

			if len(dirpath) > 0:
				includee = dirpath + "/" + includee

			tmp = assemble(includee, depth+1)
			
			if tmp:
				result += tmp
			
			else:
				return None
		
		else:
			result += line
	
	return result + "\n"

def main():
	sys.excepthook = show_exception_and_exit

	if len(sys.argv) != 4:
		sys.exit("Usage: `{0}` <input> <install output> <definition output>".format(sys.argv[0]))

	path     = sys.argv[1]
	datapath = sys.argv[2]
	defpath  = sys.argv[3]

	if not os.path.exists(path):
		sys.exit("`{0}` doesn't exist".format(path))

	(cwd, inputFile) = os.path.split(path)
	inputName = inputFile.split('.')[0]

	textList = assemble(path)

	if textList:
		definitionsheader = """// Text Definitions generated by textprocess

#ifndef TEXT_DEFINITIONS
	#define TEXT_DEFINITIONS
#endif

"""
		dataheader = """// Text Data installer generated by textprocess

#include "Tools/Tool Helpers.txt"
#include "{0}"

""".format(os.path.relpath(defpath, os.path.split(datapath)[0]))

		# Generate the files

		with open(datapath, 'w') as f:
			f.write(dataheader)
			f.write("{\n\n") # Scoping labels

		with open(defpath, 'w') as f:
			f.write(definitionsheader)

		textEntries = getEntries(textList)
		subdirectory = os.path.join(cwd, ".TextEntries")

		try:
			os.mkdir(subdirectory)
		
		except Exception:
			pass
		
		for entry in textEntries: # create separate files for each text entry
			content = entry[0]
			textID = entry[1]
			definition = entry[2]

			textFileName  = os.path.join(subdirectory, inputName + "_" + textID + ".fetxt")
			textDataLabel = "_TextData" + textID

			with open(textFileName, 'w') as f:
				f.write(content)
			
			with open(datapath, 'a') as f:
				f.write(textDataLabel + ":\n")
				f.write('#incbin "' + os.path.relpath(textFileName, cwd) +'.bin"\n')
				f.write("setText(" + textID + ", " + textDataLabel + ")\n\n")
			
			if definition:
				with open(defpath, 'a') as f:
					f.write("#define " + definition + " " + textID + "\n")

		with open(datapath, 'a') as f:
			f.write("}\n")
	
	else:
		print("No data written to output.\n")

if __name__ == '__main__':
	main()