# sql作业题

> 有数据库的表如下 ：

![image-20241219093055512](https://woniumd.oss-cn-hangzhou.aliyuncs.com/java/yujian/20241219093055.png)

### 单表查询

1. **查询所有员工的姓名和出生日期。**

```sql
select first_name,last_name,birth_date from employees 
```

2. **查询所有在1980年之后出生的员工姓名。**

```sql
select first_name,last_name, birth_date from employees where birth_date >1980
```

3. **查询性别为男的员工姓名和雇佣日期，并按雇佣日期降序排列。**

```sql
select first_name,last_name,hire_date ,gender from employees where gender = 'M' order by hire_date desc
```

4. **查询姓“Smith”的员工信息，名字可以模糊匹配。**

```sql
select first_name,last_name from employees where first_name like '%Smith%' or last_name like '%Smith%'
```

5. **分页查询员工信息，每页10条，查询第2页的数据。**

```sql
select *from employees limit 10,10
```

### 多表查询（联查）

6. **查询每个部门及其经理的姓名。**

```sql

```

7. **查询员工及其所属部门的名称。**

```sql
select e.*,de.dept_name 
from employees e
left join dept_emp d on e.emp_no = d.emp_no
left join departments de on d.dept_no = de.dept_no 
```

8. **查询在某个时间段内（例如2020-01-01至2023-12-31）在职的员工姓名和部门名称。**

```sql
select e.first_name,e.last_name,de.dept_name,e.hire_date
from employees e
join dept_emp d on e.emp_no = d.emp_no
join departments de on d.dept_no = de.dept_no 
and e.hire_date between 2020 and 2024
```

9. **查询工资在某个范围内（例如50000至60000）的员工姓名和工资。**

```sql

```

10. **查询员工姓名、职位（title）和工资，并确保这些员工在查询时（例如某个日期'2023-01-01'）仍在职。**

```sql
select e.first_name,e.last_name,t.title,s.salary,e.hire_date
from employees e
join salaries s on e.emp_no = s.emp_no
join titles t on e.emp_no = t.emp_no
and e.hire_date = '2023-01-01' 
```



参考答案：

``` sql

```



### 更复杂的查询

1. **查询在某个部门（例如'd001'）工作过的所有员工的姓名**

   ``` sql
   select e.first_name,e.last_name,d.dept_no
   from employees e
   join dept_emp d on e.emp_no = d.emp_no
   and d.dept_no = 'd001'
   ```

2. **查询从未在任何部门担任过经理的员工姓名。**

   ``` sql
   select e.emp_no,e.first_name ,e.last_name
   from employees e
   join dept_emp de on e.emp_no = de.emp_no
   where de.emp_no not in ( 1,2,10,11,12 )
   ```

3. **查询最高工资员工的姓名及部门信息。**

   ``` sql
   select e.first_name,e.last_name,d.*,s.salary
   from employees e
   join salaries s on e.emp_no = s.emp_no
   join dept_emp d on e.emp_no =d.emp_no
   and s.salary = 75000 order by s.salary asc
   ```

4. **查询同时拥有两个不同职位的员工的姓名。**

5. **查询同时拥有两个不同部门,工作经验的员工的姓名**

6. **查询每个部门在2020年的总薪水**

7. **查询工资高于所有女性员工的男性员工的姓名**

8. **查询在'Sales'部门工作的员工的姓名**

9. **查询每个部门中薪水最高的员工，如果该部门有多个员工薪水相同，则都返回**

参考答案：

``` sql

```

















