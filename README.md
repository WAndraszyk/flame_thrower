# flame_thrower
Arduino project: motion activated flamethrower

Based on and inspiried by: https://create.arduino.cc/projecthub/Advanced/punch-activated-arm-flamethrowers-real-firebending-95bb80

![alt text](https://github.com/WAndraszyk/flame_thrower/blob/main/fire_gif.gif "Test")

# How does it work?

Flame thrower is an Arduino Uno controlled project using Adafruit's LIS3DH motion sensor. The device consists of a small gas tank with an electro-valve, a lighter, a battery, a prototype board with a circuit. Gas is loaded into the tank, I use propane butane in the form of lighter gas. The plasma lighter connected to the rest of the system lights up when the punch is executed, and with it, the solenoid valve opens, through which the compressed gas comes out. The gas ignites meeting an arc of plasma from the lighter generating a flame.

![image](https://user-images.githubusercontent.com/34272444/120083526-85c26080-c0c9-11eb-89c0-e9aa3f17536c.png)

The device is activated by a switch. The whole is powered by a 7. 5V battery. Opening of electrovalve is controlled by Arduino (voltage applied to transistor). The same is true of a lighter. Since the cigarette lighter has its own power source, it is separated from the rest of the circuit by optocouplers. The lighter is controlled by two Arduino pins. The first is responsible for starting the cigarette lighter - the cigarette lighter normally starts when the lid is opened, which caused the two wires to short out. After disassembling this element, the circuit with the transistor is responsible for shorting these cables. The second circuit is responsible for applying voltage to the button that lights the already working lighter. In order to turn off the lighter, the two cables mentioned earlier need to be disconnected, thus stopping the voltage being applied to the transistor.

![alt text](https://github.com/KacperPerz/flame_thrower/blob/main/circuit.png "circuit")
