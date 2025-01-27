# Navigate to the build directory
Set-Location "./build"

# Build the project
cmake --build .

# Return to the project root
Set-Location ..
Write-Host "Build complete."
