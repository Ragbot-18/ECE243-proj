# Castle Clash - 2D Tower Defense Game on FPGA
> ECE243 Project

<div align="center">
  <img src = "https://github.com/user-attachments/assets/e4980dc5-c304-4a5e-abf6-9cf6c9ab98e1" width="350px">                            
</div>
<h3>Short Summary</h3>
Castle Clash is a 2D side-view tower defence game developed for the Intel DE1-SoC FPGA. The game features real-time projectile motion, collision detection, and custom sprite animations, all rendered using a VGA display. Player input is managed through a PS/2 keyboard, while the game logic is implemented in C and executed on the Nios II processor. The game highlights the efficient use of interrupts, low-level hardware programming, and graphics handling on an FPGA platform.

**Features:**

- Custom 2D graphics and animations
- Real-time physics and collision detection
- VGA display integration
- Keyboard-controlled gameplay
- Implemented using C on Nios II processor


<h3>About:</h3>
We created a 2d side view tower defence game where the user tries to defeat an enemy AI tower by spawning characters while making sure they don’t die. The game features custom images and characters and uses the timer and PS2 keyboard with interrupts while displaying to the VGA. 

<h3>How to use our project:</h3>

Upon the beginning of the application, the player will see a home screen and have the option to press the Space bar to start the game. When the game starts, the player will see two towers with a health bar above them, a currency counter at the top left of the screen, as well as buttons along the bottom edge of the screen. The left tower is the user’s and the right one is the enemy’s. When either tower is destroyed, the game ends on a ‘Game Over’ screen or a ‘You Win’ screen.


<div align="center">
  <img src = "https://github.com/user-attachments/assets/1c1fefa2-019e-4eb4-b311-b3d9761f9461">
</div>
<div align="center" >
  <img src = "https://github.com/user-attachments/assets/9d56daf4-0510-4889-adf1-959577f49930">
</div>

<div align="center" >
  <img src = "https://github.com/user-attachments/assets/0c30a2c7-016e-4e92-8753-495c47e8d7eb">
</div>

The user can use the number keys on the PS2 keyboard to purchase characters or upgrades for a certain amount of money. Each button has the associated cost at the top left and the key to press at the bottom. For example, for the knight button below, the user would press ‘1’ to spawn a knight for $10.

<div align="center">
<img src="https://github.com/user-attachments/assets/2d699c01-d35b-45e7-bbb8-9c35d6ed4636" width="450px">
</div>


Note: The button’s background colours have different meanings. 
- purple - not enough currency
- green - you have enough currency
- red - when key is pressed and you do not have enough currency
- blue - when key is pressed and you do have enough currency
