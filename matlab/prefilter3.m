clear, close all
I = imread('C:\Users\Kliton\Documents\Work\Imago\imago\data\from_caduff_2\IMG_0051.JPG');%'C:\Users\Kliton\Documents\Work\Imago\imago\data\december\TS_3_iPad_2_25.JPG');%'C:\Users\Kliton\Documents\Work\Imago\imago\data\from_caduff_2\IMG_0042.JPG')

I = rgb2gray(I);
I=impyramid(I,'reduce');
se = strel('disk', 13);
Itop = imtophat(255-I, se);

I=imcomplement(Itop);

e = imadjust(I, stretchlim(I), []);
e = imfilter(e, fspecial('unsharp'), 'replicate');
e = wiener2(e, [5 5]);
e = impyramid(e, 'expand');
t = graythresh(e);
%e=impyramid(e,'expand');
e = im2bw(e, 60/256);

figure, imshow(e);