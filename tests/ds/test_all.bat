echo Current date: %DATE% 1>>log1.txt

FOR /D %%G IN ("%cd%\"*) DO (
  FOR %%F IN ("%%G\*.jpg") DO (
    echo "%%G" "%%F" 1>>log1.txt
    ds_test.exe "%%F" 1>>log1.txt 2>>log2.txt
  )
)

