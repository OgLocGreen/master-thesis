from PIL import Image
 
 
img = Image.open("./panorama.png")
img = img.convert("RGB")
 
d = img.getdata()
 
new_image = []
for item in d:
 
    # change all white (also shades of whites)
    # pixels to yellow
    if item[0] in list(range(200, 256)):
        #new_image.append((255, 224, 100)) # update yellow color
        new_image.append((255, 0, 0)) # update yellow color
    else:
        new_image.append(item)
 

#Red: (255, 0, 0)
#Green: (0, 255, 0)
#Blue: (0, 0, 255)
#Yellow: (255, 255, 0)
#Cyan: (0, 255, 255)
#Magenta: (255, 0, 255)
#Orange: (255, 165, 0)
#Purple: (128, 0, 128)
#Pink: (255, 192, 203)
#Brown: (165, 42, 42)


# update image data
img.putdata(new_image)
 
# save new image
img.save("panorama_red.png")