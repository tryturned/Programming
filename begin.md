Learn Git ----Liao Xuefeng's Course  
rely on Ubuntu18.04 ,here are the steps for creating a remote warehouse   
## Generating SSH keys and append public_key to github's SSH KEYS
1. ` $ ssh-keygen -t rsa  -C "your_email@example.com"` //it will be generate at ~/.ssh
2. Add SSH Key to github //SSH Key located at ~/.ssh/id_rsa.pub  
## Adding your local warehouse to remotes 
1. mkdir learngit
2. echo "# test" >> README.md
3. git init
4. git add README.md
5. git commit -m "first commit"
6. git remote add origin git@github.com:/tryturned/learngit.git
7. git push -u origin master
>to be highly successful  
after committing local files ,we can make use of command 'git push origin master' directly
to push it out.
