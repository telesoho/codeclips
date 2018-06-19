# Remove remote branch
git push -d -r origin/branch_name
# Remove remote local branch
git branch -D branch_name

# Remove all such stale branches
git remote prune origin

# git stash
git stash
git stash list
git stash pop
git stash apply
