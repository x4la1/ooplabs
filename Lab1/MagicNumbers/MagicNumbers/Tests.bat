@echo off
SET MyProgram="%~1"
SET Out="%TEMP%\out.txt"

%MyProgram% "-find" > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output1.txt || goto err
echo 1 test passed

%MyProgram% "-find" 1 2 > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output2.txt || goto err
echo 2 test passed

%MyProgram% 1 2 > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output3.txt || goto err
echo 3 test passed

%MyProgram% < input4.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output4.txt || goto err
echo 4 test passed

%MyProgram% < input5.txt > %Out% 
IF ERRORLEVEL 1 goto err
fc %Out% output5.txt || goto err
echo 5 test passed

%MyProgram% "-find" 1 > %Out% 
IF ERRORLEVEL 1 goto err
fc %Out% output6.txt || goto err
echo 6 test passed

echo all tests passed
exit /B 0

:err
echo tests failed
exit /B 1
