# Config
config project_name: "Jump",
author: "Anshul Kharbanda",
created: "7 - 15 - 2016",
short_description: "Jump is a new programming language that uses the state machine paradigm",
long_description: "Jump is a new programming language that uses the state machine paradigm"

#--------------------------------------------MAKERS--------------------------------------------

# Header file
file :header,
path: "include/@(project_name)/@(path)",
template: "header.general",
extension: "h"

# Source file
file :source,
path: "src/@(path)",
template: "source.general",
extension: "cpp"

# Error file
file :error,
path: "include/@(project_name)/Core/Errors/@(class -> lowercase)",
template: "error.general",
extension: "h"

# Module includes a source and include
task :module do |args|
	# Add header id
	args[:header_id] = c_header_id(args[:path])

	# Create source and header
	make :header, args
	make :source, args
end