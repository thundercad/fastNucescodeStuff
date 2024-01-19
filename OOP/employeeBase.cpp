#include<iostream>
#include<string>
using namespace std;
class Name {
	string fname;
	string Iname;
public:
	Name(string f = "ali", string I = "hamza")
	{
		fname = f;
		Iname = I;
	}
	void get_name()
	{
		cout << endl;
		cout <<fname;
		cout << Iname;
	}
};
class Adress
{
	int houseNo;
	char block;
	int streetNo;
	string city;
public:
	Adress(int houseNo=0, char block='A', int streetNo=0, string city="c")
	{
		this->houseNo = houseNo;
		this->block = block;
		this->streetNo = streetNo;
		this->city = city;
	}
	void displayAddress()
	{
		cout << "house number:" << houseNo << endl;
		cout << "block number:" << block << endl;
		cout << "street number:" << streetNo << endl;
		cout << "city:" << city << endl;
	}
};
class Employee;
class Project
{
	int ID;
	int employeesWorkinOn;
	string projectDescription;
	Employee* employee[10];
public:
	Project(int ID, string projectDescription)
	{
		employeesWorkinOn = 0;
		this->ID = ID;
		this->projectDescription = projectDescription;
	}
	void displayProjectInfo();
	void Increment_employeeWorkinOn();
	void decrement_employeeWorkinOn();
	bool AddEmployee(Employee* emp);
	bool RemoveEmployee(Employee*);
	void display_all_employees();
	int getprojid();
};
class Department
{
	int ID;
	string name;
	Employee* employee[50];
	int employeeCount;
public:
	Department(int ID, string name)
	{
		this->ID = ID;
		this->name = name;
		employeeCount = 0;
	}
	void displayDeptInfo();
	bool AddEmployee(Employee* emp);
	bool RemoveEmployee(int employee_ID);
	void DisplayAllEmployees();
	int getid();
	int counter = 0;
};
class Employee
{
	int ID;
	Name name;
	Adress permanentAddr;
	bool assignedtoDept;
	Project* project[3];
	int projectCount;
	Department* Dept;
public:
	Employee(int ID, Name name, Adress permanentAddr)
	{
		int c = 0;
		this->ID = ID;
		this->name = name;
		this->permanentAddr = permanentAddr;
		Dept = nullptr;
		assignedtoDept = 0;
	}
	int get_ID();
	void show_name()
	{
		this->name.get_name();
	}
	bool AddProject(Project* proj);
	bool Remove_from_project(int Projid);
	void Display_All_Projects();
	void SetDept(Department* dept);
	void displayDept();
	void displayEmployeeinfo();
	void setassignedtodept(bool value);
	bool getassignedtoDept();
};

//employe ky functions
bool Employee::AddProject(Project* proj)
{
	if (projectCount < 3)
	{
		project[projectCount++] = proj;
		return true;
	}
	else
	{
		cout << "canot have more than three projects";
		return false;
	}
}
bool Employee::Remove_from_project(int Projid)
{
	for (int i = 0;i < projectCount;i++)
	{
		if (project[i]->getprojid() == Projid)
		{
			for (int j = i;j < projectCount - 1;j++)
			{
				project[j] = project[j + 1];
			}
			projectCount--;
			project[projectCount] = nullptr;
			return true;
		}
	}
	return false;
}
void Employee::Display_All_Projects()
{
	for (int i = 0;i < projectCount;i++)
	{
		project[i]->displayProjectInfo();
	}
}
void Employee::SetDept(Department* dept)
{
	this->Dept = dept;
	setassignedtodept(1);
}
void Employee::displayDept()
{
	Dept->displayDeptInfo();
}
void Employee::displayEmployeeinfo()
{
	cout << endl;
	cout <<"employee_id: "<<ID << endl;
	name.get_name();
	cout << endl << "projectcount: " << projectCount<<endl;
	if (getassignedtoDept() == true)
		cout << "its is assigned to a department";
	else
		cout << "not assigned to a department";
;

}
bool Employee::getassignedtoDept()
{
	return assignedtoDept;
}
void Employee::setassignedtodept(bool value)
{
	assignedtoDept = value;
}
int Employee::get_ID()
{
	return ID;
}

//project_employee_functions defined
void Project::display_all_employees()
{
		cout << "employees workin on are: "<<employeesWorkinOn<<endl;
		for (int i = 0;i < employeesWorkinOn;i++)
		{
			cout << employee[i]->get_ID();
			employee[i]->show_name();
			cout << endl;
		}
}
bool Project::AddEmployee(Employee* emp)
{
	if (employeesWorkinOn < 10)
	{
		employee[employeesWorkinOn++] = emp;
		return true;
	}
	return false;
}
bool Project::RemoveEmployee(Employee*obj)
{
	for (int i = 0;i <employeesWorkinOn;i++)
	{
		if (employee[i]== obj)
		{
			delete employee[i];
			employee[i] = nullptr;
			for (int j = i;j < employeesWorkinOn-1;j++)
			{
				employee[j] = employee[j+1];
			}
			--employeesWorkinOn;
			cout << "employee removed";
	       return true;
		}
	}
	return false;
	
}
int Project::getprojid()
{
	return ID;
}
void Project::displayProjectInfo()
{
	cout << endl;
	cout << "Project Id :" << this->ID << endl;
	cout << "Project description :" <<this-> projectDescription<<endl;
	cout << "Employees working on :" <<this->employeesWorkinOn<<endl;
}
void Project::Increment_employeeWorkinOn()
{
	++employeesWorkinOn;
}
void Project::decrement_employeeWorkinOn()
{
	--employeesWorkinOn;
}
//department_employee_functions
void Department::displayDeptInfo()
{
	cout << endl;
	cout << "Department Infromation\n";
	cout << "department ID:" << ID << endl;
	cout << "department name:" << name << endl;
	cout << "employee count:" << employeeCount;
	cout << endl;
}
bool Department::AddEmployee(Employee* emp)
{
	if (employeeCount < 50)
	{
		employee[employeeCount++] = emp;
		return true;
	}
	return false;
}
bool Department::RemoveEmployee(int employee_ID)
{
	for (int i = 0;i < employeeCount;i++)
	{
		if (employee[i]->get_ID() == employee_ID)
		{
			for (int j = i;j < employeeCount - 1;j++)
			{
				employee[j] = employee[j + 1];
			}
			--employeeCount;
			employee[employeeCount] = nullptr;
			return true;
		}
	}
		return false;
}
void Department::DisplayAllEmployees()
{
	cout << "the employees working are:" << employeeCount<<endl;
	for (int i = 0;i < employeeCount;i++)
	{
		employee[i]->displayEmployeeinfo();
		cout << endl;
	}
}
int Department::getid()
{
	return ID;
}
int main()
{
	cout << "1-Create Department\n";
	cout << "2-Create Employee\n";
	cout << "3-Create Project\n";
	cout << "4-Display A Department given its ID, (if it exists)\n";
	cout << "5-Display An Employee given its ID, (if it exists)\n";
	cout << "6-Display A Project given its ID, (if it exists)\n";
	cout << "7-Add an Employee to a Department, provided the IDs\n";
	cout << "8-Add a Project to an Employee, provided the IDs\n";
	cout << "9-Display all projects of An Employee given his/her ID\n";
	cout << "10-Display all employees of a Department given its ID\n";
	cout << "11-Remove an Employee from a Department, provided the IDs\n";
	cout << "12-Remove a Project from an Employee, provided the IDs\n";
	cout << "13-Display all Employees working on a project, provided Project ID\n";
	cout << "14-Display the Department of an Employee, provided Employee ID\n";
	int dt = 0;
	int et = 0;
	int pt = 0;
	Department* d1[5] = {};
	Employee* e1[5] = {};
	Project* p1[5] = {};
	int inp_emp = 0;
	int inp_pro = 0;
	int inp_dept = 0;
	int option = 0;
	while (option != -1)
	{
		cin >> option;
		//creat department
		if (option == 1)
		{
			string n;
			cout << "enter Id:";cin >> inp_emp;
			cout << "enter dept name:";cin >> n;
			d1[dt] = new Department(inp_emp, n);
			dt++;
		}
		//creat employee
		if (option == 2)
		{
			cout << "enter id:";
			cin >> inp_emp;
			string f1;
			string f2;
			cout << "enter first name:";

			cin >> f1;
			cout << "enter last name:";
			cin >> f2;
			Name n1(f1, f2);
			int hn = 0;
			cout << "enter house number:";
			cin >> hn;
			char b;
			cout << "enter block no:";
			cin >> b;
			string c;
			cout << "enter city name:";
			cin >> c;
			int sn = 0;
			cout << "enter street number:";
			cin >> sn;
			Adress ad(hn, b, sn, c);
			e1[et] = new Employee(inp_emp, n1, ad);
			++et;
		}
		//creat project
		if (option == 3)
		{
			cout << "ebter project id:";
			cin >> inp_pro;
			string descript;
			cout << "enter project  description:";
			cin >> descript;
			p1[pt] = new Project(inp_pro, descript);
			++pt;
		}
		//display department
		if (option == 4)
		{
			cout << "enter department id:";
			cin >> inp_dept;
			for (int i = 0;i < dt;i++)
			{
				if (d1[i]->getid() == inp_dept)
				{
					d1[i]->displayDeptInfo();

				}
			}

		}
		//display employee
		if (option == 5)
		{
			bool found = false;
			cout << "enter employee id:";
			cin >> inp_emp;
			for (int i = 0;i < dt;i++)
			{
				if (e1[i]->get_ID() == inp_emp)
				{
					e1[i]->displayEmployeeinfo();
					found = true;
					break;
				}
			}

		}
		//display project
		if (option == 6)
		{
			cout << "enter project id:";
			cin >> inp_emp;
			for (int i = 0;i < dt;i++)
			{
				if (p1[i]->getprojid() == inp_emp)
				{
					p1[i]->displayProjectInfo();
				}
			}
		}
		// Add an Employee to a Department, provided the IDs
		if (option == 7)
		{
			cout << "enter the id of deparetment:";
			cin >> inp_dept;
			cout << "enter employee id";
			cin >> inp_emp;
			for (int i = 0;i < dt;i++)
			{
				int f = 0;
				if (d1[i]->getid() == inp_dept)
				{
					for (int j = 0;j < et;j++)
					{
						if (e1[j]->get_ID() == inp_emp);
						{
							e1[j]->SetDept(d1[i]);
							d1[i]->AddEmployee(e1[j]);
							break;
						}
					}
				}
			}
		}
		// Add an project to a employee, provided the IDs
		if (option == 8)
		{
			cout << "enter project id:";
			cin >> inp_pro;
			cout << "enter employee id:";
			cin >> inp_emp;
			for (int i = 0;i < et;i++)
			{
				if (e1[i]->get_ID() == inp_emp)
				{
					for (int j = 0;j < pt;j++)
					{
						if (p1[j]->getprojid() == inp_pro)
						{
							p1[j]->AddEmployee(e1[i]);
							e1[i]->AddProject(p1[j]);
						}
					}
				}
			}

		}
		//display all projects given employee id
		if (option == 9)
		{
			cout << "enter employee id:";
			cin >> inp_emp;
			for (int i = 0;i < et;i++)
			{
				if (e1[i]->get_ID() == inp_emp)
				{
					e1[i]->Display_All_Projects();
				}
			}
		}
		//Display all employees of a Department given its ID
		if (option == 10)
		{
			cout << "enter the id of department:";
			cin >> inp_dept;
			for (int i = 0;i < dt;i++)
			{
				if (d1[i]->getid() == inp_dept)
				{
					d1[i]->DisplayAllEmployees();
				}
			}
		}
		//11 - Remove an Employee from a Department, provided the IDs
		if (option == 11)
		{
			cout << "enter id of the employee:";
			cin >> inp_emp;
			cout << "enter id of the departement:";
			cin >> inp_dept;
			for (int i = 0;i < dt;i++)
			{
				if (d1[i]->getid() == inp_dept)
				{
					for (int j = 0;j < et;j++)
					{
						if (e1[i]->get_ID() == inp_emp)
						{
							d1[i]->RemoveEmployee(inp_emp);
							e1[i]->setassignedtodept(0);
						}
					}
				}
			}
		}
		//12 - Remove a Project from an Employee, provided the IDs
		if (option == 12)
		{
			cout << "enter project id:";
			cin >> inp_pro;
			cout << "enter employee id:";
			cin >> inp_emp;
			for (int i = 0;i < et;i++)
			{
				if (e1[i]->get_ID() == inp_emp)
				{
					for (int j = 0;j < pt;j++)
					{
						if (p1[j]->getprojid() == inp_pro)
						{
							p1[j]->RemoveEmployee(e1[i]);
							e1[i]->Remove_from_project(inp_pro);
						}
					}
				}
			}
		}
		//Display all Employees working on a project, provided Project ID
		if (option == 13)
		{
			cout << "enter project id:";
			cin >> inp_pro;
			for (int i = 0;i < pt;i++)
			{
				if (p1[i]->getprojid() == inp_pro)
				{
					p1[i]->display_all_employees();
					break;
				}
			}
		}
		if (option == 14)
		{
			cout << "enter employee id:";
			cin >> inp_emp;
			for (int i = 0;i < et;i++)
			{
				if (e1[i]->get_ID() == inp_emp)
				{
					e1[i]->displayDept();
				}
			}
		}

	}
}

