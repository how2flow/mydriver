# my driver

Simple Driver Example Practice Space.<br>

Add the driver code below the `driver/`,<br>
and add the `Kconfig` and `higher Kconfig of the added path`,<br>
and the contents of the config to `arch/$ARCH/configs/defconfig` with `prefix(CONFIGS_)`.<br>

### setup

- cross compile
```
$ git clone https://github.com/how2flow/mydriver
$ cd linux
$ cp -r ~/mydriver drivers/
$ cd drivers/mydriver
$ ARCH=target_architecture CONFIG=target_config ./INSTALL
$ cd ../..
$ make ARCH=target_architecture target_config
$ make
```
<br>

- native install
```
$ git clone https://github.com/how2flow/mydriver
$ cd linux
$ sudo cp /boot/config-$(uname -r) .config
$ cp -r ~/mydriver drivers/
$ cd drivers/mydriver
$ ./INSTALL
$ cd ../..
$ make oldconfig
$ make && make install
```
<br>

### cantact

e-mail: <steve@how2flow.net>
