import skimage
import skimage.feature
import numpy as np 
import matplotlib.pyplot as plt 
import pathlib

def match(image):
    templates = np.array([item.name for item in pathlib.Path().glob('*.png')])
    img =  skimage.io.imread(image,as_gray=True)
    img = img > skimage.filters.threshold_otsu(img)
    plt.imshow(img)
    plt.show()
    results = []
    for tem in templates:
        temp = skimage.io.imread(tem,as_gray = True)
        result = skimage.feature.match_template(img,temp)
        results.append(result.max())
    resultmax = results.index(max(results))
    return templates[resultmax]
