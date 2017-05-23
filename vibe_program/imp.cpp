 std::vector<std::vector<cv::Point> > contours, contours2;
			findContours(postProcessMap, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
			Rect bounding_rect;
			vector<Mat> cropImage;
			double areaMin = 25;
			double areaMax = 100;
			std::vector<cv::Point2f> features, ffeatures;
			int numDet = 0;
			
			vector<Mat> channels;
			channels.push_back(segmentationMap);
			channels.push_back(segmentationMap);
			channels.push_back(segmentationMap);
			merge(channels, segmentationMap);
			Mat finalIm;
			for (int i = 0; i < contours.size(); i++)
			{
				if ((contourArea(contours[i]) > areaMin) && (contourArea(contours[i]) < areaMax))
				{
					Rect rect = boundingRect(contours[i]);
					rectangle(frame, Rect(rect.x - 2, rect.y - 2, rect.width + 5, rect.height + 3), Scalar(0, 0, 255), 1, 8, 0);
					putText(frame, "(Main Frame) Frame Number: " + std::to_string(frameCount), cvPoint(wd / 2-550, ht - 25), FONT_HERSHEY_PLAIN, 4, CV_RGB(0, 0, 225), 4, CV_AA);
					putText(foreGround, "(Moving Objects only) Fm No: " + std::to_string(frameCount), cvPoint(wd / 2-550, ht - 25), FONT_HERSHEY_PLAIN, 4, CV_RGB(225, 225, 225), 3, CV_AA);
					putText(backGround, "(Background Image) Fm No: " + std::to_string(frameCount), cvPoint(wd / 2-550, ht - 25), FONT_HERSHEY_PLAIN, 3, CV_RGB(0, 0, 225), 3, CV_AA);
					resize(frame, frame, Size(wd /3, ht / 2));
					//resize(foreGround, foreGround, Size(wd / 3, ht / 2));
					//resize(backGround, backGround, Size(wd / 3, ht / 2));
					finalIm=concat1.imageConcat(frame, segmentationMap);
					imshow("frame", finalIm);
					//vidW << frame;
					waitKey(1);
				}
			}