echo "Building the game..."

# Build the game.
# 切换到 source 目录
Set-Location "source"

# 获取所有 .cpp 文件的完整路径
$cppFiles = Get-ChildItem -Filter *.cpp | ForEach-Object { $_.FullName }

# 编译并链接
g++ $cppFiles -o ../output/main.exe -lsfml-graphics -lsfml-window -lsfml-system


# Run the game if the build is successful.
if ($LASTEXITCODE -eq 0) {
    ../output/main.exe
} else {
    Write-Host "Build failed. Please check the errors above."
    pause
}

