
obj-m = chardev.o

all:
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:	
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) clean 

