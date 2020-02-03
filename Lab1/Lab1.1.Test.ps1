$lab11_exe = Resolve-Path "**/Lab1.1.exe"

Write-Output "Testing $lab11_exe..."

Write-Output "Program for no arguments should return error"
.$lab11_exe
if($LASTEXITCODE -eq 0) {
	throw "Program succeeded for no arguments"
} else {
	Write-Host "Test passed" -BackgroundColor Green
}

Write-Output "Program for unknown argument should return error"
.$lab11_exe -q
if($LASTEXITCODE -eq 0) {
	throw "Program succeeded for no arguments"
} else {
	Write-Host "Test passed" -BackgroundColor Green
}

Write-Output "Program for -e argument should succeed"
.$lab11_exe -e
if($LASTEXITCODE -ne 0) {
	throw "Program failed for -e argument"
} else {
	Write-Host "Test passed" -BackgroundColor Green
}

Write-Output "Program for -e argument should print memory error"
$out = .$lab11_exe -e
if("$out".Contains("Not enough memory")) {
	Write-Host "Test passed" -BackgroundColor Green
} else {
	throw "Program has not printed memory error"
}

Write-Output "Program for -s argument should succeed"
.$lab11_exe -s
if($LASTEXITCODE -ne 0) {
	throw "Program failed for -s argument"
} else {
	Write-Host "Test passed" -BackgroundColor Green
}

Write-Output "Program for -s argument should print memory status"
$out = .$lab11_exe -s
if("$out".Contains("percent of memory in use")) {
	Write-Host "Test passed" -BackgroundColor Green
} else {
	throw "Program has not printed memory status"
}
