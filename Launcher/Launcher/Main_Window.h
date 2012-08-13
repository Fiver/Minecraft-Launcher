#pragma once

namespace Launcher {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Main_Window
	/// </summary>
	public ref class Main_Window : public System::Windows::Forms::Form
	{
	public:
		Main_Window(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Main_Window()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::WebBrowser^  webBrowser1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
		this->button1 = (gcnew System::Windows::Forms::Button());
		this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
		this->webBrowser1 = (gcnew System::Windows::Forms::WebBrowser());
		this->SuspendLayout();
		// 
		// button1
		// 
		this->button1->Location = System::Drawing::Point(12, 467);
		this->button1->Name = L"button1";
		this->button1->Size = System::Drawing::Size(597, 25);
		this->button1->TabIndex = 0;
		this->button1->Text = L"Play Minecraft";
		this->button1->UseVisualStyleBackColor = true;
		this->button1->Click += gcnew System::EventHandler(this, &Main_Window::button1_Click);
		// 
		// linkLabel1
		// 
		this->linkLabel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
			static_cast<System::Byte>(0)));
		this->linkLabel1->LinkColor = System::Drawing::Color::Black;
		this->linkLabel1->Location = System::Drawing::Point(12, 396);
		this->linkLabel1->Name = L"linkLabel1";
		this->linkLabel1->Size = System::Drawing::Size(597, 68);
		this->linkLabel1->TabIndex = 1;
		this->linkLabel1->TabStop = true;
		this->linkLabel1->Text = L"Launcher is in standby, press Play to scan files for modifications.";
		// 
		// webBrowser1
		// 
		this->webBrowser1->Location = System::Drawing::Point(12, 12);
		this->webBrowser1->MinimumSize = System::Drawing::Size(20, 20);
		this->webBrowser1->Name = L"webBrowser1";
		this->webBrowser1->Size = System::Drawing::Size(597, 381);
		this->webBrowser1->TabIndex = 2;
		// 
		// Main_Window
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(621, 504);
		this->Controls->Add(this->webBrowser1);
		this->Controls->Add(this->linkLabel1);
		this->Controls->Add(this->button1);
		this->Name = L"Main_Window";
		this->Text = L"Main_Window";
		this->ResumeLayout(false);

			}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 // Obscure this how you like, would recommend dropping msvf support for security, we just need this to prevent people using xray texture packs or xray mods.
				 // Since I haven't seen any memory injectors for minecraft this is fairly simple, yet clumsy as a list of known good MD5s must be parsed, essentially building a whitelist
				 // of mods and texture packs that are allowed... which may turn into a lengthy process.
				 // 
				 // Currently this renames the server list file and puts our server list file in it's place.

				 // Builds current directory buffer
				 char CurrentDirectory = "%appdata%\.minecraft\bin";

				 // Find first file
				 string FileToScan = FindFirstFile( CurrentDirectory );

				 // Checks first file
				 string CalculatedFileMD5 = MD5.digestFile(FileToScan); 

				 do 
					 {
					 string FileToScan = FindNextFile(CurrentDirectory)
					 MD5.digestFile(FileToScan)
					 } while (FindNextFile);

				 char *EstablishedMD5s [] = {
					 "" // Current Unmodified 1.3.1
					 };

				 bool IsKnownArchive=false;

				 for ( int n=0; n < countof(EstablishedMD5s); n++ )
					 {
					 if (CalculatedFileMD5 == EstablishedMD5s[n])
						 {
						 IsKnownArchive=true; // this is set to true to prevent the error message from coming up which is below
						 // stop iterating md5s
						 n = countof(EstablishedMD5s);
						 }
					 }

				 if (IsKnownArchive == false)
					 {
						 cout << "File \""<<szFileName<<"\" does NOT match any known MD5, refusing to launch." << endl;
						 cout << "Press any key..." << endl;
						 cin.get();
						 exit(0);
						 }
					 // write to log, for lazy saving of MD5s later on when I add more to the list of valid MD5s
					 ofstream myfile;
					 myfile.open("Logs\\MD5-Check.log");
					 myfile << "A MD5 was unmatched in \""<<szFileName<<"\"" << endl
						 << CalculatedFileMD5 << endl << endl;
					 myfile.close();
					 }

				 delete [] szFileName;
				 cout << endl;

				 }
		};

