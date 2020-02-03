$lab12_exe = Resolve-Path "**/Lab1.2.exe"
$source_acii = Resolve-Path "source_ascii.txt"
$source_unicode = Resolve-Path "source_unicode.txt"

Write-Host "Testing $lab12_exe..."

Write-Host "Program for no arguments should return an error" -ForegroundColor Yellow
.$lab12_exe
if($LASTEXITCODE -eq 0) {
	throw "Program succeeded for no arguments"
} else {
	Write-Host "Test passed" -ForegroundColor Green
}

Write-Host "Program for unknown argument should return an error" -ForegroundColor Yellow
.$lab12_exe -q $source_acii "target"
if($LASTEXITCODE -eq 0) {
	throw "Program succeeded for unknown"
} else {
	Write-Host "Test passed" -ForegroundColor Green
}

Write-Host "Program when source does not exist should return an error" -ForegroundColor Yellow
.$lab12_exe -a "source" "target"
if($LASTEXITCODE -eq 0) {
	throw "Program succeeded for invalid source"
} else {
	Write-Host "Test passed" -ForegroundColor Green
}
