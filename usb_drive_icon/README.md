# Custom USB Drive Icon
1. Download icons
   * Go to e.g. [findicons.com](https://findicons.com/icon/86048/usb_stick) and download `.ico` and `.icns` of some icon, say [this](https://findicons.com/icon/86048/usb_stick).
   * Rename them to `drive.ico` and `drive.icns` before copy steps below. Otherwise the `.icns` will retain it's old name after Finder copy.
1. macOS ([reference](https://www.howtogeek.com/293835/how-to-change-the-hard-drive-icons-on-your-mac/))
   1. Finder: copy the `.icns file`
   1. Finder: cmd+i on the drive
   1. Click on the top left icon in the window and cmd+v paste the icon.
1. Windows ([reference](https://windowsloop.com/change-usb-drive-icon-windows/))
   1. Copy [autorun.inf](autorun.inf) to the disk's root.
   1. Copy your icon as `drive.ico` to the disk's root.
   1. Explorer: select `autorun.inf`, `drive.ico` and `drive.icns` > right click > Properties > check "Hidden" attribute.
