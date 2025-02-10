SET MyProgram="%~1"
SET Out="%TEMP%\out.txt"


%MyProgram% input1.txt privet poka > %Out% || goto err
fc %Out% output1.txt > nul|| goto err
echo 1 test passed

%MyProgram% input2.txt > %Out% || goto err
fc %Out% output2.txt > nul|| goto err
echo 2 test passed

%MyProgram% input3.txt "" > %Out% || goto err
fc %Out% output3.txt > nul|| goto err
echo 3 test passed

%MyProgram% unknown.txt privet > %Out% || goto err
fc %Out% output4.txt > nul|| goto err
echo 4 test passed

%MyProgram% input5.txt privet > %Out% || goto err
fc %Out% output5.txt > nul|| goto err
echo 5 test passed

%MyProgram% input5.txt privet > %Out% || goto err
fc %Out% output5.txt > nul|| goto err
echo 5 test passed

%MyProgram% input6.txt privet > %Out% || goto err
fc %Out% output6.txt > nul|| goto err
echo 6 test passed

%MyProgram% input7.txt privet > %Out% || goto err
fc %Out% output7.txt > nul|| goto err
echo 7 test passed


echo all tests passed
exit /B 0

:err
echo tests failed
exit /B 1
