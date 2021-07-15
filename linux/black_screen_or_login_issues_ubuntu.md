# Black Screen Or Login Issues (Ubuntu)

Copy from: https://support.system76.com/articles/login-loop-ubuntu

ometimes after an upgrade, your system might not bring you to the desktop after logging in. If you try logging in and you just see a black screen, or Pop!_OS brings you back to the login screen, you're experiencing a login loop. 

In most cases, you can switch to a full-screen terminal (called a TTY) to log in and fix the issue.

## Switch to a Terminal

At the login screen, press **Ctrl+Alt+F5** to switch to a TTY. You'll be prompted to enter a login. At the login prompt, enter your username and press Enter. You'll then be prompted for your password. You will not see your password as you are typing it; just type it and press "Enter."

After logging in, you'll be presented with a prompt showing your username, hostname, and a tilde (~) representing your home directory.

Login and initial prompt

Note that you can always return to the graphical login screen by pressing **Ctrl+Alt+F1**, or by typing sudo systemctl restart gdm.

## Move old configuration files out of the way

To determine whether configuration in your home directory is causing the issue, you can create a new user account for testing purposes:

```sh
sudo adduser test
sudo systemctl reboot
```

If you're able to log in with the test user, the issue is somewhere in your regular user's home folder. Log into the full-screen terminal with your regular user again, and move some of the common configuration files out of the way:

```sh
mv ~/.config ~/.config.old
mv ~/.local ~/.local.old
mv ~/.cache ~/.cache.old
mv ~/.nvidia-settings-rc ~/.nvidia-settings-rc.old
mv ~/.nv ~/.nv.old
sudo systemctl reboot
```

After moving those files and rebooting, try logging in again. (There may be files you need to move other than the common ones listed above.)

## Reinstall the login manager
You can reinstall GNOME Display Manager (which handles the login screen), along with the desktop environment by running the below commands in :

```sh
sudo apt install --reinstall gdm3 ubuntu-desktop gnome-shell
sudo systemctl reboot
```

After reinstalling those packages and rebooting, try logging in again.


## Blacklist Radeon Driver
If you are using an AMD graphics card, the radeon driver might be causing issues as it does not support newer versions of Ubuntu. The amdgpu driver that comes with the kernel does however. To blacklist the radeon driver and ensure amdgpu is loaded:

Open /etc/modprobe.d/blacklist.conf for editing and add blacklist radeon to the file. Then run:

```sh
sudo update-initramfs -c -k all
sudo shutdown -r now
```

If these steps don't work
Contact Support! We have a few more things to try. There are a significant number of processes and files required for your graphical desktop environment to be loaded, and much fewer for the terminal login. As such, you can usually recover your desktop using the command line interface!

