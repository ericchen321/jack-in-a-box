# author: Larry Liu, Eric Chen, Bole Ma
# use pattern matching to recognize digits on cards

import skimage
import skimage.feature
import skimage.io
import numpy as np 
import matplotlib.pyplot as plt 
import matplotlib.patches as mpatches
import pathlib
from skimage.filters import threshold_otsu
from skimage.segmentation import clear_border
from skimage.measure import label, regionprops
from skimage.morphology import closing, square
from skimage.color import label2rgb

# construct black/white templates from raw template images;
# require raw images 'raw_1.jpeg' to 'raw_13.jpeg'
# save templates to 'template_1.jpeg' to 'template_13.jpeg'
def build_templates():
    template_raw_paths = np.array([item.name for item in pathlib.Path().glob('raw*.jpeg')])
    counter = 1
    for template_raw_path in template_raw_paths:
        print("start processing: " + template_raw_path)
        template = skimage.io.imread(template_raw_path, as_gray=True)
        template = template > skimage.filters.threshold_otsu(template)
        """plt.imshow(template)
        plt.show()
        template = closing(template, square(3))
        # remove artifacts connected to image border
        cleared = clear_border(template)
        # label image regions
        label_image = label(cleared)
        image_label_overlay = label2rgb(label_image, image=template)
        fig, ax = plt.subplots(figsize=(10, 6))
        ax.imshow(image_label_overlay)
        for region in regionprops(label_image):
            # take regions with large enough areas
            if region.area >= 1000:
                # draw rectangle around segmented coins
                minr, minc, maxr, maxc = region.bbox
                rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
                                        fill=False, edgecolor='red', linewidth=2)
                ax.add_patch(rect)
        ax.set_axis_off()
        plt.tight_layout()
        plt.show()"""
        skimage.io.imsave(('template_' + str(counter) + '.jpeg'), skimage.img_as_uint(template))
        counter += 1

# load templates from files, then match a raw image 
def match(image):
    # load templates
    templates = []
    template_bw_paths = np.array([item.name for item in pathlib.Path().glob('template_*.png')])
    for template_bw_path in template_bw_paths:
        template = skimage.io.imread(template_bw_path, as_gray=True)
        templates.append(template)
    
    # construct b/w test image
    img =  skimage.io.imread(image,as_gray=True)
    img = img > skimage.filters.threshold_otsu(img)
    plt.imshow(img)
    plt.show()

    # match
    results = []
    for temp in templates:
        print("comparing with template...")
        result = skimage.feature.match_template(img,temp)
        results.append(result.max())
    print(results)
    resultmax = results.index(max(results))
    return template_bw_paths[resultmax]
