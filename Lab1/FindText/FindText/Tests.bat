SET MyProgram="%~1"
SET Out="%TEMP%\out.txt"


%MyProgram% input1.txt privet poka > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output1.txt || goto err
echo 1 test passed

%MyProgram% input2.txt > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output2.txt || goto err
echo 2 test passed

%MyProgram% input3.txt "" > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output3.txt || goto err
echo 3 test passed

%MyProgram% unknown.txt privet > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output4.txt || goto err
echo 4 test passed

%MyProgram% input5.txt privet > %Out%
IF ERRORLEVEL 1 goto err
fc %Out% output5.txt || goto err
echo 5 test passed

%MyProgram% input6.txt privet > %Out% 
IF ERRORLEVEL 1 goto err
fc %Out% output6.txt || goto err
echo 6 test passed

%MyProgram% input7.txt privet > %Out%
IF ERRORLEVEL 1 goto err
fc %Out% output7.txt || goto err
echo 7 test passed

%MyProgram% input8.txt privet > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output8.txt || goto err
echo 8 test passed

%MyProgram% input9.txt privet > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output9.txt || goto err
echo 9 test passed


echo all tests passed
exit /B 0

:err
echo tests failed
exit /B 1
