Mờ trong ảnh được mô tả bằng Point Spread Function (PSF) [2], có thể thể hiện đơn giản như hình bên dưới [4]:
Có 4  kiểu mờ (blurring) phổ biến trong ảnh [2] là:  
1. Mờ do lệch khỏi tiêu cự (Out of Focus or Defocus): Đây là loại mờ do tiêu cự không đúng. Phương trình:
Ở đây, R là bán kính, theo bán kính của PSF size sẽ tính.
Kiểu mờ này tương tự như tật khúc xạ, một số hình ảnh [5]
2. Mờ do object chuyển động (Motion Blur): loại mờ này do object di chuyển nhanh hơn tốc độ phơi sáng của máy ảnh (hoặc camera). Hình ảnh [7]:
3. Box Blur: là kiểu làm mờ tuyến tính trong miền không gian (spatial domain). Mỗi pixel là kết quả trung bình giá trị của pixels xung quanh trong input image.
4. Gaussian Blur: là làm mờ bằng hàm Gaussian. Như phương trình bên dưới:


Hai kiểu mờ 1 & 2 là tuyến tính (blur linear). Mờ xuất hiện theo 1 hướng nhất định và có xu hướng tròn tại góc [2]. So sánh với ảnh output, dễ nhận thấy kiểu mờ của ảnh không thuộc 2 kiểu này.

Hai kiểu mờ 3 & 4 là dùng phương pháp phổ biến để làm mờ (blurring) ảnh là low-pass filter [1]. 


[1] Rohina Ansari,Himanshu Yadav,Anurag Jain,” A Survey on Blurred Images with Restoration and Transformation Techniques”, International Journal of Computer Applications (0975 - 8887) Volume 68- No.22, April 2013.
[2] Fagun Vankawala, et all ,“ A Survey on different Image Deblurring Techniques”, International Journal of Computer Applications (0975 - 8887) Volume 116- No.13, April 2015.
[3] A.Mahalakshmi, B.Shanthini, “A Survey on Image Deblurring”, International Conference on Computer Communication and Informatics (ICCCI – 2016), Jan. 07- 09, 2016, Coimbatore, India.
[4] https://en.wikipedia.org/wiki/Point_spread_function
[5] https://en.wikipedia.org/wiki/Defocus_aberration
[6] https://en.wikipedia.org/wiki/Gaussian_blur
[7] https://en.wikipedia.org/wiki/Motion_blur

