void _DFT(){
 //1�ԻҶ�ģʽ��ȡԭͼ����ʾ
 Mat srcImage = imread("miFan.jpg",0);
 if (!srcImage.data){ cout << "Error\n"; }
 imshow("ԭͼ��", srcImage);
 
 //2������ͼ����չ����ѳߴ�,�߽���0����
 int m = getOptimalDFTSize(srcImage.rows);
 int n = getOptimalDFTSize(srcImage.cols);
 
 //����ӵ����س�ʼ��Ϊ0
 Mat padded;
 copyMakeBorder(srcImage, padded, 0, m - srcImage.rows,
  0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
 
 //3Ϊ����Ҷ�任�Ľ��(ʵ�����鲿)����洢�ռ�
 //��������Ϻϲ�Ϊһ����ͨ������
 Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
 Mat complexI;
 merge(planes, 2, complexI);
 
 //4���и���Ҷ�任
 dft(complexI, complexI);
 
 //5������ת��Ϊ��ֵ����=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
 //����ͨ���������Ϊ������ͨ������
 split(complexI, planes);//planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
 magnitude(planes[0], planes[1], planes[0]);
 Mat magImage = planes[0];
 
 //6���ж����߶�����
 magImage += Scalar::all(1);
 log(magImage, magImage);//����Ȼ����
 
 //7���к��طֲ�����ͼ����
 //���������л������У�����Ƶ�׼���
 magImage = magImage(Rect(0, 0, magImage.cols&-2, magImage.rows&-2));
 //�������и���Ҷͼ���е����ޣ�ʹ��ԭ��λ��ͼ������ 
 int cx = magImage.cols / 2;
 int cy = magImage.rows / 2;
 Mat q0(magImage, Rect(0, 0, cx, cy));
 Mat q1(magImage, Rect(cx, 0, cx, cy));
 Mat q2(magImage, Rect(0,cy,cx,cy));
 Mat q3(magImage, Rect(cx,cy,cx,cy));
 //��������(���������½��н���)
 Mat tmp;
 q0.copyTo(tmp);
 q3.copyTo(q0);
 tmp.copyTo(q3);
 //�������ޣ����������½��н�����
 q1.copyTo(tmp);
 q2.copyTo(q1);
 tmp.copyTo(q2);
 
 //8��һ������0��1�ĸ���ֵ������任Ϊ���ӵ�ͼ���ʽ
 normalize(magImage, magImage, 0, 1, CV_MINMAX);
 
 //9��ʾ
 imshow("Ƶ������", magImage);
 
 waitKey();
}
