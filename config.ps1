# Create the build directory if it doesn't exist
if (!(Test-Path -Path "./build")) {
    New-Item -ItemType Directory -Path "./build" | Out-Null
}

# Navigate to the build directory
Set-Location "./build"

# Run the CMake configuration
cmake -G "Ninja" ..

# Return to the project root
Set-Location ..
Write-Host "Configuration complete."
