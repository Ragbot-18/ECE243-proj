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
        file.write(f"const short int Number_9[{height * width}] = {{\n")
        
        for y in range(height):
            for x in range(width):
                r, g, b = pixels[y][x]
                color_16bit = rgb_to_16bit(r, g, b)
                file.write(f"0x{color_16bit:04X}, ")
            file.write("\n")
        
        file.write("};\n")

image_path = 'small num_0.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_0.txt')
image_path = 'small num_1.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_1.txt')
image_path = 'small num_2.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_2.txt')
image_path = 'small num_3.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_3.txt')
image_path = 'small num_4.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_4.txt')
image_path = 'small num_5.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_5.txt')
image_path = 'small num_6.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_6.txt')
image_path = 'small num_7.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_7.txt')
image_path = 'small num_8.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_8.txt')
image_path = 'small num_9.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_9.txt')
image_path = 'small num_10.png'  # Replace with your image path
image_to_c_array_file(image_path, 'small num_10.txt')
