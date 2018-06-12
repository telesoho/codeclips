https://stackoverflow.com/questions/20627084/permission-denied-var-www-abc-htaccess-pcfg-openfile-unable-to-check-htacces

Make sure that the htaccess file is readable by apache:

chmod 644 /var/www/abc/.htaccess 
And make sure the directory it's in is readable and executable:

chmod 755 /var/www/abc/
