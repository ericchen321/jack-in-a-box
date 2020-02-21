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

template_bw_paths = []
templates = []

# construct black/white template images from preprocessed images;
# require preprocessed images 'prep_01.jpeg' to 'prep_13.jpeg'
# save template images to 'template_01.jpeg' to 'template_13.jpeg'
def build_templates():
    template_raw_paths = np.array([item.name for item in pathlib.Path().glob('prep*.jpeg')])
    for template_raw_path in template_raw_paths:
        print("start processing: " + template_raw_path)
        template = skimage.io.imread(template_raw_path, as_gray=True)
        template = template > skimage.filters.threshold_otsu(template)
        # flip bits in template
        template = np.invert(template)
        # crop out unnecessary parts
        template = closing(template, square(3))
        # remove border stuff
        cleared = clear_border(template)
        plt.imshow(cleared)
        plt.show()
        # label image regions
        label_image = label(cleared)
        region_area_max = 0
        region_digit = None
        # find region with max area. This should be the one with digits
        for region in regionprops(label_image):
            # take regions with large enough areas
            minr, minc, maxr, maxc = region.bbox
            if region.area > region_area_max:
                region_digit = cleared[minr:maxr, minc:maxc]
                region_area_max = region.area
                print(f"region has area: {region_digit.shape}")
        assert region_digit is not None
        plt.imshow(region_digit)
        plt.show()
        template_digit = template_raw_path[5:7]
        skimage.io.imsave(('template_' + template_digit + '.jpeg'), skimage.img_as_uint(region_digit))

# construct black/white template image from 
# given preprocessed image; crop with specified
# x and y coords
def build_template(template_raw_path, x_0, x_1, y_0, y_1):
    print("start processing: " + template_raw_path)
    template = skimage.io.imread(template_raw_path, as_gray=True)
    template = template > skimage.filters.threshold_otsu(template)
    # flip bits in template
    template = np.invert(template)
    # crop out unnecessary parts
    template = closing(template, square(3))
    plt.imshow(template)
    plt.show()
    # remove border stuff
    #cleared = clear_border(template)
    #plt.imshow(cleared)
    #plt.show()
    # label image regions
    label_image = label(template)
    region_area_max = 0
    region_digit = None
    # find region with max area. This should be the one with digits
    minr_max, minc_max, maxr_max, maxc_max = 0, 0, 0, 0 
    for region in regionprops(label_image):
        # take regions with large enough areas
        minr, minc, maxr, maxc = region.bbox
        if region.area > region_area_max:
            minr_max, minc_max, maxr_max, maxc_max = region.bbox
            region_digit = template[minr:maxr, minc:maxc]
            region_area_max = region.area
            print(f"region has area: {region_digit.shape}")
    assert region_digit is not None
    print (f"max region has dimensions: {minc_max}, {maxc_max}, {minr_max}, {maxr_max}")
    print (f"selected crop area: {x_0}, {x_1}, {y_0}, {y_1}")
    region_digit = template[y_0:y_1, x_0:x_1]
    plt.imshow(region_digit)
    plt.show()
    template_digit = template_raw_path[5:7]
    skimage.io.imsave(('template_' + template_digit + '.jpeg'), skimage.img_as_uint(region_digit))

# populate the templates array from template images;
# require 'template_01.jpeg' to 'template_13.jpeg' present
def load_templates():
    global templates
    templates = []
    global template_bw_paths
    template_bw_paths = []
    template_bw_paths = np.array([item.name for item in pathlib.Path().glob('template_*.jpeg')])
    for template_bw_path in template_bw_paths:
        print("loading template from " + template_bw_path)
        template = skimage.io.imread(template_bw_path, as_gray=True)
        templates.append(template)
    assert len(templates)==13

# match templates with the given test image;
# require load_templates() called;
# return the filename of the test image matched
def match(image):
    # check templates loaded
    if len(templates) != 13:
        print("should load templates first! length of templates: " + str(len(templates)))
        return "error"
    
    # construct b/w test image
    img =  skimage.io.imread(image,as_gray=True)
    img = img > skimage.filters.threshold_otsu(img)

    # crop out unnecessary parts
    img = closing(img, square(3))
    # remove border stuff
    cleared = clear_border(img)
    # label image regions
    label_image = label(cleared)
    region_area_max = 0
    region_digit = None
    # find region with max area. This should be the one with digits
    for region in regionprops(label_image):
        # take regions with large enough areas
        minr, minc, maxr, maxc = region.bbox
        if region.area > region_area_max:
            region_digit = cleared[minr:maxr, minc:maxc]
            region_area_max = region.area
    assert region_digit is not None
    plt.imshow(region_digit)
    plt.show()

    # match
    results = []
    for temp in templates:
        print("comparing with template...")
        result = skimage.feature.match_template(region_digit,temp)
        results.append(result.max())
    print(results)
    resultmax = results.index(max(results))
    return template_bw_paths[resultmax]