

# Working with branches using git commands


Fist, we have to create a branch and move to it, for this purpose we can use:

```
git branch <BRANCH_NAME>
git checkout <BRANCH_NAME>
```

Once we are in the new branch we can start editing the needed files.

Then we need to commit the changes:

```
git add <modified_files>
git commit -m "Comments"
```


The only thing that remains is to merge back the new branch with the main branch.
To do so we first need to go back to the main branch, we can do it using:

```
git checkout main
```

Finally we can merge the changes and push them to the remote repository.

```
git merge <BRANCH_NAME>
git push -u origin main
```

We can check the status with:

```
git status
```
