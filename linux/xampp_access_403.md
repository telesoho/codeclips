Setup an virtual host will cause 403 access error.
The fastest way to correct it:
Move your virtual host folder to htdocs.

# AH00035: access to / denied (filesystem path '/Users/xxx/Documents/workspace') because search permissions are missing on a component of the path
https://stackoverflow.com/questions/43318041/ah00035-access-to-denied-filesystem-path-users-xxx-documents-workspace-b

namei -mol /Users/xxx/Documents/workspace/firstRepo/htdocs
