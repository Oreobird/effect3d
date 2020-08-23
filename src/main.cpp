
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include <iostream>

#include "DetectorManager.h"
#include "EffectManager.h"
#include "VideoHandler.h"
#include "ImageHandler.h"


static void showHelp() 
{
    std::cout << "effect3d --file input_file\n"
			  << "        [--video output_video]\n"
			  << "        [--image output_image]\n"
			  << "        --detector yolact\n"
			  << "        --effect lr|rl"
              << std::endl;
}

typedef struct _opt 
{
    std::string filePath;
    std::string video;
    std::string detector;
    std::string effect;
    std::string image;
} opt_t;

int processCommandLine(int argc, char** argv, opt_t &opt) 
{
    enum OPTIONS 
    {
        OPT_HELP = 0,
        OPT_IN_FILE,
        OPT_OUT_VIDEO,
        OPT_OUT_IMAGE,
        OPT_DETECTOR,
        OPT_EFFECT
    };

    const int noArgument = 0;
    const int requiredArgument = 1;

    static struct option s_longOptions[] = 
    {
            {"help",             noArgument,       NULL, OPT_HELP},
            {"file",             requiredArgument, NULL, OPT_IN_FILE},
            {"video",            requiredArgument, NULL, OPT_OUT_VIDEO},
            {"image",            requiredArgument, NULL, OPT_OUT_IMAGE},
            {"detector",         requiredArgument, NULL, OPT_DETECTOR},
            {"effect",           requiredArgument, NULL, OPT_EFFECT},
            {NULL, 0, NULL, 0}
    };

    int longIndex = 0;
    int opt_idx = 0;

    while ((opt_idx = getopt_long_only(argc, argv, "", s_longOptions, &longIndex)) != -1) 
    {
        switch (opt_idx) 
        {
            case OPT_HELP:
                showHelp();
                std::exit(0);
            case OPT_IN_FILE:
                opt.filePath = optarg;
                break;
            case OPT_OUT_VIDEO:
                opt.video = optarg;
                break;
            case OPT_OUT_IMAGE:
                opt.image = optarg;
                break;
            case OPT_DETECTOR:
                opt.detector = optarg;
                break;
            case OPT_EFFECT:
                opt.effect = optarg;
                break;
            default:
                fprintf(stderr, "Invalid argument passed: %s", argv[optind - 1]);
                showHelp();
                std::exit(-1);
        }
    }

    return 0;
}


int main(int argc, char** argv)
{
    opt_t opt;

    processCommandLine(argc, argv, opt);

    if (!opt.video.empty() && !opt.image.empty()) 
    {
        return -1;
    }

    auto detectorMgt = DetectorManager::create();
    auto detector = detectorMgt->createDetector(opt.detector);

    auto effectMgt = EffectManager::create();
    auto effect = effectMgt->createEffect(opt.effect);
    
    if (!opt.video.empty()) 
    {
        auto videoHandler = std::make_shared<VideoHandler>(opt.detector, opt.effect);
        videoHandler->preProcess(opt.filePath);
        videoHandler->doTask();
        videoHandler->postProcess(opt.video);
    } 
    else if (!opt.image.empty()) 
    {
        auto imgHandler = std::make_shared<ImageHandler>(opt.detector, opt.effect);
        imgHandler->preProcess(opt.filePath);
        imgHandler->doTask();
        imgHandler->postProcess(opt.image);
    }

    return 0;
}
