#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "Effect3d.h"


int LREffect::draw(cv::Mat& image, const std::vector<Object>& objects) 
{
    std::cout << "----Left to right effect----" << std::endl;

    int left_x = image.cols/3;
    int right_x = image.cols/3*2;

    bool has_major_obj = false;

    for (size_t i = 0; i < objects.size(); i++)
    {
        const Object& obj = objects[i];
//            float ratio = obj.rect.area() / (image.rows * image.cols);

        if (obj.prob < 0.5 ) 
        {
            continue;
        }

        has_major_obj = true;
        // draw white line

        // left line
        std::vector<cv::Point> points;
        points.emplace_back(cv::Point(left_x, 1));
        bool is_mask = false;

        for (int y = 0; y < image.rows; y++)
        {
            const uchar* mp = obj.mask.ptr(y);
            if (mp[left_x] == 255 && !is_mask)
            {
                is_mask = true;
                points.emplace_back(cv::Point(left_x, y));
            }
            else if (mp[left_x] == 0 && is_mask)
            {
                is_mask = false;
                points.emplace_back(cv::Point(left_x, y));
            }
        }
        points.emplace_back(cv::Point(left_x, image.rows - 1));

        for (int j = 0; j < (int)points.size(); j += 2)
        {
            cv::line(image, points[j], points[j + 1], cv::Scalar(255, 255, 255), 4, -1);
        }

        // right line
        cv::line(image, cv::Point(right_x, 1), cv::Point(right_x, image.rows - 1), cv::Scalar(255,255,255), 4, -1);
    }

    if (!has_major_obj)
    {
        cv::line(image, cv::Point(left_x, 1), cv::Point(left_x, image.rows - 1),
                    cv::Scalar(255,255,255), 4, -1);
        cv::line(image, cv::Point(right_x, 1), cv::Point(right_x, image.rows - 1),
                    cv::Scalar(255,255,255), 4, -1);
    }
    return 0;
}



int RLEffect::draw(cv::Mat& image, const std::vector<Object>& objects) 
{
    std::cout << "----Right to left effect----" << std::endl;

    int left_x = image.cols/3;
    int right_x = image.cols/3*2;

    bool has_major_obj = false;

    for (size_t i = 0; i < objects.size(); i++)
    {
        const Object& obj = objects[i];

        if (obj.prob < 0.5 ) 
        {
            continue;
        }

        has_major_obj = true;
        // draw white line

        // left line
        std::vector<cv::Point> points;
        points.emplace_back(cv::Point(right_x, 1));
        bool is_mask = false;

        for (int y = 0; y < image.rows; y++)
        {
            const uchar* mp = obj.mask.ptr(y);
            if (mp[right_x] == 255 && !is_mask)
            {
                is_mask = true;
                points.emplace_back(cv::Point(right_x, y));
            }
            else if (mp[right_x] == 0 && is_mask)
            {
                is_mask = false;
                points.emplace_back(cv::Point(right_x, y));
            }
        }
        points.emplace_back(cv::Point(right_x, image.rows - 1));

        for (int j = 0; j < (int)points.size(); j += 2)
        {
            cv::line(image, points[j], points[j + 1], cv::Scalar(255, 255, 255), 4, -1);
        }

        // right line
        cv::line(image, cv::Point(left_x, 1), cv::Point(left_x, image.rows - 1), cv::Scalar(255,255,255), 4, -1);
    }

    if (!has_major_obj)
    {
        cv::line(image, cv::Point(left_x, 1), cv::Point(left_x, image.rows - 1),
                    cv::Scalar(255,255,255), 4, -1);
        cv::line(image, cv::Point(right_x, 1), cv::Point(right_x, image.rows - 1),
                    cv::Scalar(255,255,255), 4, -1);
    }
    return 0;
}



static void draw_inout_line(const std::vector<Object>& objects, int left_x, int right_x, cv::Mat& image) 
{
    bool has_major_obj = false;

    for (size_t i = 0; i < objects.size(); i++)
    {
        const Object& obj = objects[i];

        if (obj.prob < 0.5 ) 
        {
            continue;
        }

        has_major_obj = true;
        // draw white line

        // left line
        std::vector<cv::Point> points;
        points.push_back(cv::Point(left_x, 1));
        bool is_mask = false;

        for (int y = 0; y < image.rows; y++)
        {
            const uchar* mp = obj.mask.ptr(y);
            if (mp[left_x] == 255 && !is_mask)
            {
                is_mask = true;
                points.push_back(cv::Point(left_x, y));
            }
            else if (mp[left_x] == 0 && is_mask)
            {
                is_mask = false;
                points.push_back(cv::Point(left_x, y));
            }
        }
        points.push_back(cv::Point(left_x, image.rows - 1));

        for (int j = 0; j < (int)points.size(); j += 2)
        {
            cv::line(image, points[j], points[j + 1], cv::Scalar(255, 255, 255), 4, -1);
        }

        // right line
        points.clear();
        points.push_back(cv::Point(right_x, 1));
        is_mask = false;

        for (int y = 0; y < image.rows; y++)
        {
            const uchar* mp = obj.mask.ptr(y);
            if (mp[right_x] == 255 && !is_mask)
            {
                is_mask = true;
                points.push_back(cv::Point(right_x, y));
            }
            else if (mp[right_x] == 0 && is_mask)
            {
                is_mask = false;
                points.push_back(cv::Point(right_x, y));
            }
        }
        points.push_back(cv::Point(right_x, image.rows - 1));

        for (int j = 0; j < (int)points.size(); j += 2)
        {
            cv::line(image, points[j], points[j + 1], cv::Scalar(255, 255, 255), 4, -1);
        }
    }

    if (!has_major_obj)
    {
        cv::line(image, cv::Point(left_x, 1), cv::Point(left_x, image.rows - 1),
                 cv::Scalar(255,255,255), 4, -1);
        cv::line(image, cv::Point(right_x, 1), cv::Point(right_x, image.rows - 1),
                 cv::Scalar(255,255,255), 4, -1);
    }
}

static cv::Mat draw_3d_in_out(const cv::Mat& bgr, const std::vector<Object>& objects, bool half_count, bool near_to_far)
{
    cv::Mat image = bgr.clone();

    int left_x = image.cols/3;
    int right_x = image.cols/3*2;

    if (near_to_far) 
    {
        if (half_count) 
        {
            draw_inout_line(objects, left_x, right_x, image);
        } 
        else 
        {
            cv::line(image, cv::Point(left_x, 1), cv::Point(left_x, image.rows - 1),
                     cv::Scalar(255, 255, 255), 4, -1);
            cv::line(image, cv::Point(right_x, 1), cv::Point(right_x, image.rows - 1),
                     cv::Scalar(255, 255, 255), 4, -1);
        }
    } 
    else 
    {
        if (half_count) 
        {
            cv::line(image, cv::Point(left_x, 1), cv::Point(left_x, image.rows - 1),
                     cv::Scalar(255, 255, 255), 4, -1);
            cv::line(image, cv::Point(right_x, 1), cv::Point(right_x, image.rows - 1),
                     cv::Scalar(255, 255, 255), 4, -1);
        }
        else 
        {
            draw_inout_line(objects, left_x, right_x, image);
        }
    }

    return image;
}

int NFEffect::draw(cv::Mat& image, const std::vector<Object>& objects) 
{
    std::cout << "----Near to far effect----" << std::endl;
    return 0;
}


int FNEffect::draw(cv::Mat& image, const std::vector<Object>& objects) 
{
    std::cout << "----Far to near effect----" << std::endl;
    return 0;
}


