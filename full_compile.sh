cd /usr/src/linux
make bzImage
make modules
make 
make modules_install
make install

sleep 10
