import os
# list all main folder anad avoid the git folder
main_folder=[i for i in os.listdir() if os.path.isdir(i) and i!=".git"]

for a in main_folder:
    for i,j,k in os.walk(a):
        # checking the folder is empty or not
        if not os.listdir(i):
            file_name="empty_file.txt"
            with open("{}/{}".format(i,file_name),"w") as file:
                file.write("")
        
