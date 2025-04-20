DDServerCore : 실제 IOCP가 구현되어 있는 라이브러리 프로젝트
  - DDServerWork.sln 솔루션 파일으로 직접 빌드 혹은 DDServerWork_Build_x64.bat, DDServerWork_Build_x86.bat 이걸로 빌드
  - 다만 비주얼 스튜디오 2022 커뮤니티가 C:\Program Files\Microsoft Visual Studio\2022\Community 이 경로에 설치되어있어야함.

DDServerCore의 빌드가 끝나면 ExternalModules 안에 lib, .h, .hpp, .inl 파일들이 담기게 되고, 이것들은 Projects의 DDClientTest, DDServerMain 여기에서 쓰이게 됨.

그리고 TestClient.sln는 테스트 클라이언트, TestServer.sln는 테스트 서버, 즉 솔루션 이름 그대로 테스트이며, 실제로 포트를 열고 외부 IP에서 Accept 되는 것을 확인함.