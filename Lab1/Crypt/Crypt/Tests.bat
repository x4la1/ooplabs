
SET MyProgram="%~1"
SET Out="%TEMP%\out.txt"

%MyProgram% a b c d e > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output1.txt || goto err
echo 1 test passed

%MyProgram% a b c > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output2.txt || goto err
echo 2 test passed

%MyProgram% abc input3.txt output3.txt 121 > %Out%
IF NOT ERRORLEVEL 1 goto err
fc %Out% output3.txt || goto err
echo 3 test passed

%MyProgram% crypt input4.txt output4.txt asd > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output4.txt || goto err
echo 4 test passed

%MyProgram% crypt asdads.txt output5.txt 123 > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output5.txt || goto err
echo 5 test passed

%MyProgram% crypt input6.txt output6.txt 123 > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output6.txt || goto err
echo 6 test passed

%MyProgram% crypt input7.txt asdasddas.txt 123 > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output7.txt || goto err
echo 7 test passed

%MyProgram% crypt input8.txt %Out% 100
IF ERRORLEVEL 1 goto err
fc %Out% output8.txt || goto err
echo 8 test passed

%MyProgram% decrypt input9.txt %Out% 100
IF  ERRORLEVEL 1 goto err
fc %Out% output9.txt || goto err
echo 9 test passed

%MyProgram% crypt input4.txt output4.txt 256 > %Out% 
IF NOT ERRORLEVEL 1 goto err
fc %Out% output4.txt || goto err
echo 10 test passed

echo All tests passed
exit 0

:err
echo Program testing failed
exit 1