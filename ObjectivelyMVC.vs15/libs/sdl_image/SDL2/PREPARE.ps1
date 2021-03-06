If (!(Test-Path tmp3.zip)) {
    Write-Output "Downloading SDL_image..."
    (New-Object System.Net.WebClient).DownloadFile("https://www.libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.1-VC.zip", "tmp3.zip")
}

Write-Output "Extracting SDL_image..."
7z e tmp3.zip -aoa "SDL2_image-2.0.1\include\*.h"
7z e tmp3.zip -aoa "SDL2_image-2.0.1\lib\x86\*" -o"..\lib\Win32\"
7z e tmp3.zip -aoa "SDL2_image-2.0.1\lib\x64\*" -o"..\lib\x64\"