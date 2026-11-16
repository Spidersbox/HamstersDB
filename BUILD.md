• linux build:
sudo apt-get install build-essential
sudo apt-get install qtmultimedia5-dev

qmake
make

strip HamstersDB
sudo cp HamstersDB /usr/bin


• if you want an icon for your desktop, you will need to convert the favicon.ico to .png
cd src/images
sudo apt update && sudo apt install icoutils
icotool -x favicon.ico

mv favicon_1_96x96x32.png ~/.local/share/icons/HamstersDB.png

• create a .desktop file
vim ~/.local/share/applications/HamstersDB.desktop

[Desktop Entry]
Version=1.0
Type=Application
Name=HamstersDB
Exec=/usr/bin/HamstersDB
Icon=/home/YOUR_NAME/.local/share/icons/HamstersDB.png
Terminal=false

*copy the HamstersDB.desktop file to your Desktop
cp ~/.local/share/applications/HamstersDB.desktop ~/Desktop

• Enable launching on Ubuntu 22.04. If you put the .desktop file on your Desktop or in a folder, Ubuntu blocks custom icons until you explicitly trust the file:
• Right-click the myqtapp.desktop file in the file manager.
• Select Allow Launching.
• The file will immediately transform into your custom icon and launch your app when double-clicked.

