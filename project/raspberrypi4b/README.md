### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(sts21 REQUIRED)
```

### 3. STS21

#### 3.1 Command Instruction

1. Show sts21 chip and driver information.

   ```shell
   sts21 (-i | --information)
   ```

2. Show sts21 help.

   ```shell
   sts21 (-h | --help)
   ```

3. Show sts21 pin connections of the current board.

   ```shell
   sts21 (-p | --port)
   ```

4. Run sts21 register test.

   ```shell
   sts21 (-t reg | --test=reg)
   ```

5. Run sts21 read test, num is test times.

   ```shell
   sts21 (-t read | --test=read) [--times=<num>]
   ```


6. Run sts21 read function, num is read times.

   ```shell
   sts21 (-e read | --example=read) [--times=<num>]
   ```

7. Run sts21 sn function.

   ```shell
   sts21 (-e sn | --example=sn)
   ```

#### 3.2 Command Example

```shell
./sts21 -i

sts21: chip is Sensirion STS21.
sts21: manufacturer is Sensirion.
sts21: interface is IIC.
sts21: driver version is 1.0.
sts21: min supply voltage is 2.1V.
sts21: max supply voltage is 3.6V.
sts21: max current is 0.33mA.
sts21: max temperature is 125.0C.
sts21: min temperature is -40.0C.
```

```shell
./sts21 -p

sts21: SCL connected to GPIO3(BCM).
sts21: SDA connected to GPIO2(BCM).
```

```shell
./sts21 -t reg

sts21: chip is Sensirion STS21.
sts21: manufacturer is Sensirion.
sts21: interface is IIC.
sts21: driver version is 1.0.
sts21: min supply voltage is 2.1V.
sts21: max supply voltage is 3.6V.
sts21: max current is 0.33mA.
sts21: max temperature is 125.0C.
sts21: min temperature is -40.0C.
sts21: start register test.
sts21: sts21_set_mode/sts21_get_mode test.
sts21: set hold master mode.
sts21: check mode ok.
sts21: set no hold master mode.
sts21: check mode ok.
sts21: sts21_set_resolution/sts21_get_resolution test.
sts21: set resolution t 14bit.
sts21: check resolution ok.
sts21: set resolution t 12bit.
sts21: check resolution ok.
sts21: set resolution t 13bit.
sts21: check resolution ok.
sts21: set resolution t 11bit.
sts21: check resolution ok.
sts21: sts21_set_heater/sts21_get_heater test.
sts21: enable heater.
sts21: check heater ok.
sts21: disable heater.
sts21: check heater ok.
sts21: sts21_set_disable_otp_reload/sts21_get_disable_otp_reload test.
sts21: enable disable otp reload.
sts21: check disable otp reload ok.
sts21: disable disable otp reload.
sts21: check disable otp reload ok.
sts21: sts21_get_status test.
sts21: check vdd 2.25v status over.
sts21: sts21_get_serial_number test.
sts21: sn 0x31 0x01 0x98 0x4D 0x2E 0x5D 0x80 0x00.
sts21: sts21_soft_reset test.
sts21: soft reset.
sts21: finish register test.
```

```shell
./sts21 -t read --times=3

sts21: chip is Sensirion STS21.
sts21: manufacturer is Sensirion.
sts21: interface is IIC.
sts21: driver version is 1.0.
sts21: min supply voltage is 2.1V.
sts21: max supply voltage is 3.6V.
sts21: max current is 0.33mA.
sts21: max temperature is 125.0C.
sts21: min temperature is -40.0C.
sts21: start read test.
sts21: set hold master mode.
sts21: set resolution t 14bit.
sts21: temperature is 25.05C.
sts21: temperature is 25.05C.
sts21: temperature is 25.05C.
sts21: set resolution t 12bit.
sts21: temperature is 25.04C.
sts21: temperature is 25.04C.
sts21: temperature is 25.00C.
sts21: set resolution t 13bit.
sts21: temperature is 25.04C.
sts21: temperature is 25.02C.
sts21: temperature is 25.02C.
sts21: set resolution t 11bit.
sts21: temperature is 24.95C.
sts21: temperature is 24.95C.
sts21: temperature is 24.95C.
sts21: set no hold master mode.
sts21: set resolution t 14bit.
sts21: temperature is 25.02C.
sts21: temperature is 25.02C.
sts21: temperature is 25.02C.
sts21: set resolution t 12bit.
sts21: temperature is 25.00C.
sts21: temperature is 25.00C.
sts21: temperature is 25.00C.
sts21: set resolution t 13bit.
sts21: temperature is 25.00C.
sts21: temperature is 25.00C.
sts21: temperature is 25.00C.
sts21: set resolution t 11bit.
sts21: temperature is 24.95C.
sts21: temperature is 24.95C.
sts21: temperature is 24.95C.
sts21: finish read test.
```

```shell
./sts21 -e read --times=3

sts21: 1/3.
sts21: temperature is 24.85C.
sts21: 2/3.
sts21: temperature is 24.85C.
sts21: 3/3.
sts21: temperature is 24.85C.
```

```shell
./sts21 -e sn

sts21: sn 0x31 0x01 0x98 0x4D 0x2E 0x5D 0x80 0x00.
```

```shell
./sts21 -h

Usage:
  sts21 (-i | --information)
  sts21 (-h | --help)
  sts21 (-p | --port)
  sts21 (-t reg | --test=reg)
  sts21 (-t read | --test=read) [--times=<num>]
  sts21 (-e read | --example=read) [--times=<num>]
  sts21 (-e sn | --example=sn)

Options:
  -e <read | sn>, --example=<read | sn>
                        Run the driver example.
  -h, --help            Show the help.
  -i, --information     Show the chip information.
  -p, --port            Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                        Run the driver test.
      --times=<num>     Set the running times.([default: 3])
```
