# account

Basic user account management suite as a shared library, built against Qt 6.4. Uses a MySQL database for the backend. I'm kind of duplicating the standard webapp form-based authentication system such as in my account-php project, which is a CakePHP plugin. This project may become a Qt plugin, as well.

The lib needs to send emails, so I've included [cutelyst/simple-mail](https://github.com/cutelyst/simple-mail)
