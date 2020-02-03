$lab11_exe = Resolve-Path "**/Lab1.1.exe"

Write-Host "Testing $lab11_exe..."

Write-Host "Program for no arguments should return an error" -ForegroundColor Yellow
.$lab11_exe
if($LASTEXITCODE -eq 0) {
	throw "Program succeeded for no arguments"
} else {
	Write-Host "Test passed" -ForegroundColor Green
}

Write-Host "Program for unknown argument should return an error" -ForegroundColor Yellow
.$lab11_exe -q
if($LASTEXITCODE -eq 0) {
	throw "Program succeeded for no arguments"
} else {
	Write-Host "Test passed" -ForegroundColor Green
}

Write-Host "Program for -e argument should succeed" -ForegroundColor Yellow
.$lab11_exe -e
if($LASTEXITCODE -ne 0) {
	throw "Program failed for -e argument"
} else {
	Write-Host "Test passed" -ForegroundColor Green
}

Write-Host "Program for -e argument should print a memory error" -ForegroundColor Yellow
$out = .$lab11_exe -e
if("$out".Contains("Not enough memory")) {
	Write-Host "Test passed" -ForegroundColor Green
} else {
	throw "Program has not printed a memory error"
}

Write-Host "Program for -s argument should succeed" -ForegroundColor Yellow
.$lab11_exe -s
if($LASTEXITCODE -ne 0) {
	throw "Program failed for -s argument"
} else {
	Write-Host "Test passed" -ForegroundColor Green
}

Write-Host "Program for -s argument should print a memory status" -ForegroundColor Yellow
$out = .$lab11_exe -s
if("$out".Contains("percent of memory in use")) {
	Write-Host "Test passed" -ForegroundColor Green
} else {
	throw "Program has not printed memory status"
}
