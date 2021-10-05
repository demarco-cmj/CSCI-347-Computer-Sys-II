#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>

#define THREADS 4

#define filterWidth 3
#define filterHeight 3

#define RGB_MAX 255

typedef struct
{
    unsigned char r, g, b;
} PPMPixel;

struct parameter
{
    PPMPixel *image;         //original image
    PPMPixel *result;        //filtered image
    unsigned long int w;     //width of image
    unsigned long int h;     //height of image
    unsigned long int start; //starting point of work
    unsigned long int size;  //equal share of work (almost equal if odd)
};

/*This is the thread function. It will compute the new values for the region of image specified in params (start to start+size) using convolution.
    (1) For each pixel in the input image, the filter is conceptually placed on top ofthe image with its origin lying on that pixel.
    (2) The  values  of  each  input  image  pixel  under  the  mask  are  multiplied  by the corresponding filter values.
    (3) The results are summed together to yield a single output value that is placed in the output image at the location of the pixel being processed on the input.
 
 */
void *threadfn(void *params)
{
    struct parameter *p = (struct parameter *)params;
    unsigned long int w = p->w;
    unsigned long int h = p->h;
    unsigned long int start = p->start;
    unsigned long int size = p->size;
    PPMPixel *image = p->image;
    PPMPixel *result = p->result;
<<<<<<< HEAD
    double red, green, blue;

for (int i = start; i < start + size; i++)
    { //itterates through each row within the thread's range(starts at start, moves for size distance)
        for (int j = 0; j < w; j++)
        { //loop that iterates over width of image one pixel at a time.
            for (int k = 0; k < filterHeight; k++) //this point on is getting all of the needed data from each surrounding pixel, compiling the data and then uding it for the one pixel in the second loop
            { //loop that iterates over the filters height
                for (int n = 0; n < filterWidth; n++)
                { //loop that iterates over the filters width
                    int laplacian[filterWidth][filterHeight] =
                        {
                            -1,-1,-1,
                            -1, 8,-1,
                            -1,-1,-1,
                        };
                    int x_coordinate = (j - filterWidth / 2 + n + w) % w;
                    int y_coordinate = (i - filterHeight / 2 + k + h) % h;
=======
    int laplacian[filterWidth][filterHeight] =
        {
            -1,
            -1,
            -1,
            -1,
            8,
            -1,
            -1,
            -1,
            -1,
        };
    double red = 0.0, green = 0.0, blue = 0.0;
    int x_coordinate, y_coordinate;
    for (int i = start; i < start + size; i++)
    { //loop that iterates over pixel data?
        for (int j = 0; j < w; j++)
        { //loop that iterates over width of img
            red = 0.0;
            green = 0.0;
            blue = 0.0;
            for (int k = 0; k < filterHeight; k++)
            { //loop that iterates over the filters height
                for (int n = 0; n < filterWidth; n++)
                { //loop that iterates over the filters width
                    x_coordinate = (j - filterWidth / 2 + n + w) % w;
                    y_coordinate = (i - filterHeight / 2 + k + h) % h;
>>>>>>> b5b8b565bf97866f1e5c0f2de69efff61dc5b3db
                    red += image[y_coordinate * w + x_coordinate].r * laplacian[k][n];
                    green += image[y_coordinate * w + x_coordinate].g * laplacian[k][n];
                    blue += image[y_coordinate * w + x_coordinate].b * laplacian[k][n];
                }
            }
            if (red < 0)
                red = 0;

            if (red > 255)
                red = 255;

            if (green < 0)
                green = 0;

            if (green > 255)
                green = 255;

            if (blue < 0)
                blue = 0;

            if (blue > 255)
                blue = 255;

            result[i * w + j].r = red;
            result[i * w + j].g = green;
            result[i * w + j].b = blue;
        }
    }

    return NULL;
}

/*Create a new P6 file to save the filtered image in. Write the header block
 e.g. P6
      Width Height
      Max color value
 then write the image data.
 The name of the new file shall be "name" (the second argument).
 */
void writeImage(PPMPixel *image, char *name, unsigned long int width, unsigned long int height)
{
    FILE *fp = fopen(name, "wb+");
    //print header info
    fprintf(fp, "P6\n%lu %lu\n%d\n", width, height, 255);

    size_t tot = width * height;

    //write the function
    int num = fwrite(image, sizeof(PPMPixel), tot, fp);

    if (num != tot)
    {
        printf("Cannot write image data to the file");
        exit(1);
    }

    fclose(fp);
}

/* Open the filename image for reading, and parse it.
    Example of a ppm header:    //http://netpbm.sourceforge.net/doc/ppm.html
    P6                  -- image format
    # comment           -- comment lines begin with
    ## another comment  -- any number of comment lines
    200 300             -- image width & height
    255                 -- max color value
 
 Check if the image format is P6. If not, print invalid format error message.
 Read the image size information and store them in width and height.
 Check the rgb component, if not 255, display error message.
 Return: pointer to PPMPixel that has the pixel data of the input image (filename)
 */
PPMPixel *readImage(const char *filename, unsigned long int *width, unsigned long int *height)
{
    FILE *fp;
    fp = fopen(filename, "rb");

    if (!fp)
    {
        printf("Couldnt open file\n");
        exit(1);
    }

    PPMPixel *img;
    char x, y, c;
    int rgb;

    //read image format
    fscanf(fp, "%c %c\n", &x, &y);
    if ((x != 'P') || y != '6')
    {
        printf("File is not a ppm!\n");
        exit(1);
    }
    c = getc(fp);
    //While the comment is there and theres white space,
    while (c == '#')
    {
        do
        {
            c = getc(fp);
        } while (c != '\n');
        c = getc(fp);
    }
    //move back incase we over extended
    ungetc(c, fp);
    fscanf(fp, "%lu %lu\n", width, height);

    //Read rgb component. Check if it is equal to RGB_MAX. If  not, display error message.
    fscanf(fp, "%d\n", &rgb);
    if (rgb != RGB_MAX)
    {
        printf("File's RGB is not 255, try again!");
        exit(0);
    }
    //Memory allocation
    img = malloc((sizeof(PPMPixel) * *width * *height));
    size_t tot = *height * *width;

    fread(img, sizeof(PPMPixel), tot, fp);

    fclose(fp);

    return img;
}

/* Create threads and apply filter to image.
 Each thread shall do an equal share of the work, i.e. work=height/number of threads.
 Compute the elapsed time and store it in *elapsedTime (Read about gettimeofday).
 Return: result (filtered image)
 */
PPMPixel *apply_filters(PPMPixel *image, unsigned long w, unsigned long h, double *elapsedTime)
{
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    PPMPixel *result;

    result = malloc(w * h * sizeof(PPMPixel));
<<<<<<< HEAD
    //allocate memory for parameters (one for each thread)
    int threads = 10;
    //TODO HERE JUST NEED TO ALLOCATE PARAMETERS HERE SIR

    //elapsedTime = gettimeofday(&cur_time,NULL); //FIX ELAPSED TIME
    /*create threads and apply filter.
     For each thread, compute where to start its work.  Determine the size of the work. If the size is not even, the last thread shall take the rest of the work.
     */
=======

    int threads = 100;

    //Initialize parameter and threads, then do work on them
>>>>>>> b5b8b565bf97866f1e5c0f2de69efff61dc5b3db
    double work = h / threads;
    int size = work;
    pthread_t arr[threads];
    struct parameter tempP[threads];
    for (int i = 0; i < threads; i++)
    {
        double start = work * i;
        tempP[i].size = size;
        tempP[i].start = start;
        tempP[i].w = w;
        tempP[i].h = h;
        tempP[i].image = image;
        tempP[i].result = result;

        if ((threads - i) == 1)
            tempP[i].size = h - start;

        //make sure thread is being created successfully
        if (pthread_create(&arr[i], NULL, threadfn, (void *)(&tempP[i])) != 0)
        {
            printf("Error while creating a thread");
            exit(1);
        }
    }
    //Let threads wait till they all finish their work.
    for (int j = 0; j < threads; j++)
        pthread_join(arr[j], (void *)result);

    gettimeofday(&end_time, NULL);
    *elapsedTime = ((end_time.tv_sec - start_time.tv_sec) * 1e6 + (end_time.tv_usec - start_time.tv_usec)) / 1e6;

    return result;
}

/*The driver of the program. Check for the correct number of arguments. If wrong print the message: "Usage ./a.out filename"
    Read the image that is passed as an argument at runtime. Apply the filter. Print elapsed time in .3 precision (e.g. 0.006 s). Save the result image in a file called laplacian.ppm. Free allocated memory.
 */
int main(int argc, char *argv[])
{
    struct parameter params;
    unsigned long int w, h;
    double elapsedTime = 0.0;
    char *name = "laplacian.ppm";

    if (argc != 2)
    {
        printf("Usage ./imath filename");
        return 0;
    }
    //Call on functions to apply filter and read image
    else
    {
        //Vars
        struct timeval start, end;
        time_t startTime;
        time_t endTime;

        params.image = readImage(argv[1], &w, &h);
<<<<<<< HEAD
        gettimeofday(&start, NULL);
        params.result = apply_filters(params.image, w, h, &elapsedTime);
        gettimeofday(&end, NULL);
        long sec = (end.tv_sec - start.tv_sec);
        long mic = ((sec * 1000000) + end.tv_usec) - (start.tv_usec);
 
        printf("\nElapsed time: %ld seconds, %ld microseconds\n", sec, mic);
        //printf("Elapsed time : %ld", endTime);
        writeImage(params.result, name, w, h);
=======
        params.result = apply_filters(params.image, w, h, &elapsedTime);
        printf("Elapsed time : %.3lf s \n", elapsedTime);
        writeImage(params.result, name, w, h);
        free(params.result);
        free(params.image);
>>>>>>> b5b8b565bf97866f1e5c0f2de69efff61dc5b3db
    }

    return 0;
}
