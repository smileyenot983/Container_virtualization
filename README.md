# Running:

  1. Compile(gcc container_check -o container_check.exe)
  2. Run as super user(sudo ./container_check.exe)

# Benchmarks:
 - There are results of benchmarks for my container(benchmarks) and for docker(docker_benchmarks). 
 - To run benchmarks with my container just uncomment lines 62-68(they are under BENCHMARKS comment)
 - To run benchmarks with docker use attached dockerfile with my_bash.sh script(edit script to choose which benchmarks you want to run)

# Cgroups:
Cgroups feature is available, uncomment lines 100-110 to run. However, for some reason network does not work while running with cgroups enabled.

# Report:
Report with me personal feelings about containerization is in Ramil Khafizov report.docx
