
SET MyProgram="%~1"
SET Out="%TEMP%\out.txt"

%MyProgram% a b > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output1.txt || goto err
echo 1 test passed

%MyProgram% -h > %Out% 
IF ERRORLEVEL 1 goto err
fc %Out% output2.txt || goto err
echo 2 test passed

%MyProgram% input3.txt > %Out%
IF ERRORLEVEL 1 goto err
fc %Out% output3.txt || goto err
echo 3 test passed

%MyProgram% input4.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output4.txt || goto err
echo 4 test passed

%MyProgram% aaaa.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output5.txt || goto err
echo 5 test passed

%MyProgram% < input6.txt > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output6.txt || goto err
echo 6 test passed

%MyProgram% < input7.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output7.txt || goto err
echo 7 test passed

%MyProgram% < input8.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output8.txt || goto err
echo 8 test passed

%MyProgram% < input9.txt > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output9.txt || goto err
echo 9 test passed

%MyProgram% < input10.txt > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output10.txt || goto err
echo 10 test passed

%MyProgram% input11.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output11.txt || goto err
echo 11 test passed

%MyProgram% input12.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output12.txt || goto err
echo 12 test passed

%MyProgram% input13.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output13.txt || goto err
echo 13 test passed

%MyProgram% input14.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output14.txt || goto err
echo 14 test passed

%MyProgram% input15.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output15.txt || goto err
echo 15 test passed

%MyProgram% input16.txt > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output16.txt || goto err
echo 16 test passed

%MyProgram% input17.txt > %Out% 
IF ERRORLEVEL 1 goto err
fc %Out% output17.txt || goto err
echo 17 test passed

echo All tests passed
exit 0

:err
echo Program testing failed
exit 1