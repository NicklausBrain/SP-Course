$lab12_exe = Resolve-Path "**/Lab1.2.exe"
$source_acii = Resolve-Path "source_ascii.txt"
$source_unicode = Resolve-Path "source_unicode.txt"
$target_ascii = "target_ascii.txt"
$target_unicode = "target_unicode.txt"

if(Test-Path $target_ascii){
	Remove-Item $target_ascii
}

if(Test-Path $target_unicode){
	Remove-Item $target_unicode
}

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

Write-Host "Program when ascii source is valid should create a unicode output" -ForegroundColor Yellow
.$lab12_exe -a $source_acii $target_unicode
if($LASTEXITCODE -ne 0) {
	throw "Program failed"
}
if((Test-Path $target_unicode) -eq $false){
	throw "Target file was not created"
}
if(Get-Content $target_unicode){
	Write-Host "Test passed" -ForegroundColor Green
}
else {
	throw "Target file is empty"
}

Write-Host "Program when unicode source is valid should create an ascii output" -ForegroundColor Yellow
.$lab12_exe -u $source_unicode $target_ascii
if($LASTEXITCODE -ne 0) {
	throw "Program failed"
}
if((Test-Path $target_ascii) -eq $false){
	throw "Target file was not created"
}
if(Get-Content $target_ascii){
	Write-Host "Test passed" -ForegroundColor Green
}
else {
	throw "Target file is empty"
}