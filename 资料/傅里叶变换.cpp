void _DFT(){
 //1以灰度模式读取原图像并显示
 Mat srcImage = imread("miFan.jpg",0);
 if (!srcImage.data){ cout << "Error\n"; }
 imshow("原图像", srcImage);
 
 //2将输入图像扩展到最佳尺寸,边界用0补充
 int m = getOptimalDFTSize(srcImage.rows);
 int n = getOptimalDFTSize(srcImage.cols);
 
 //将添加的像素初始化为0
 Mat padded;
 copyMakeBorder(srcImage, padded, 0, m - srcImage.rows,
  0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
 
 //3为傅里叶变换的结果(实部和虚部)分配存储空间
 //将数组组合合并为一个多通道数组
 Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
 Mat complexI;
 merge(planes, 2, complexI);
 
 //4进行傅里叶变换
 dft(complexI, complexI);
 
 //5将复数转换为幅值，即=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
 //将多通道数组分离为几个单通道数组
 split(complexI, planes);//planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
 magnitude(planes[0], planes[1], planes[0]);
 Mat magImage = planes[0];
 
 //6进行对数尺度缩放
 magImage += Scalar::all(1);
 log(magImage, magImage);//求自然对数
 
 //7剪切和重分布幅度图象限
 //若有奇数行或奇数列，进行频谱剪裁
 magImage = magImage(Rect(0, 0, magImage.cols&-2, magImage.rows&-2));
 //重新排列傅立叶图像中的象限，使得原点位于图像中心 
 int cx = magImage.cols / 2;
 int cy = magImage.rows / 2;
 Mat q0(magImage, Rect(0, 0, cx, cy));
 Mat q1(magImage, Rect(cx, 0, cx, cy));
 Mat q2(magImage, Rect(0,cy,cx,cy));
 Mat q3(magImage, Rect(cx,cy,cx,cy));
 //交换象限(左上与右下进行交换)
 Mat tmp;
 q0.copyTo(tmp);
 q3.copyTo(q0);
 tmp.copyTo(q3);
 //交换象限（右上与左下进行交换）
 q1.copyTo(tmp);
 q2.copyTo(q1);
 tmp.copyTo(q2);
 
 //8归一化，用0到1的浮点值将矩阵变换为可视的图像格式
 normalize(magImage, magImage, 0, 1, CV_MINMAX);
 
 //9显示
 imshow("频谱增幅", magImage);
 
 waitKey();
}
