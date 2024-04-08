from PIL import Image
import numpy as np
def rgb_to_16bit(red, green, blue):
    # Convert 8-bit RGB to 5/6/5 16-bit value
    return ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3)
def image_to_c_array_file(image_path, output_file):
    # Load image
    img = Image.open(image_path)
    img = img.convert('RGB')  # Ensure it's in RGB format
    
    width, height = img.size
    pixels = np.array(img)  # Convert image to numpy array
    
    # Open output file
    with open(output_file, 'w') as file:
        file.write(f"const short int Number_[{height * width}] = {{\n")
        
        for y in range(height):
            for x in range(width):
                r, g, b = pixels[y][x]
                color_16bit = rgb_to_16bit(r, g, b)
                file.write(f"0x{color_16bit:04X}, ")
            file.write("\n")
        
        file.write("};\n")

image_path = 'Knight_Button1.png'  # Replace with your image path
image_to_c_array_file(image_path, 'Knight_Button1.txt')
image_path = 'Knight_Button2.png'  # Replace with your image path
image_to_c_array_file(image_path, 'Knight_Button2.txt')
image_path = 'Knight_Button3.png'  # Replace with your image path
image_to_c_array_file(image_path, 'Knight_Button3.txt')
image_path = 'Knight_Button4.png'  # Replace with your image path
image_to_c_array_file(image_path, 'Knight_Button4.txt')
image_path = 'Currency_Button1.png'  # Replace with your image path
image_to_c_array_file(image_path, 'Currency_Button1.txt')
image_path = 'Currency_Button2.png'  # Replace with your image path
image_to_c_array_file(image_path, 'Currency_Button2.txt')
image_path = 'Currency_Button3.png'  # Replace with your image path
image_to_c_array_file(image_path, 'Currency_Button3.txt')
image_path = 'Currency_Button4.png'  # Replace with your image path
image_to_c_array_file(image_path, 'Currency_Button4.txt')

image_path = 'intro_background.png'  # Replace with your image path
image_to_c_array_file(image_path, 'intro_background.txt')
image_path = 'win_background.png'  # Replace with your image path
image_to_c_array_file(image_path, 'win_background.txt')
image_path = 'lose_background.png'  # Replace with your image path
image_to_c_array_file(image_path, 'lose_background.txt')