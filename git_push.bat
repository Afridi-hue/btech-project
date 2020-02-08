python check_empty_folder.py
git add *
set /p message="Message to commit: "
git commit -m "%message%"
git push
pause