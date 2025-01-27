# Define the path to the executable
$executable = "./build/output/GameOfLife.exe"

# Check if the executable exists
if (Test-Path -Path $executable) {
    # Run the executable
    Start-Process Wait -FilePath $executable
} else {
    Write-Host "Executable not found. Please build the project first."
}
