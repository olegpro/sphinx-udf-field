# Sphinx UDF BK_FIELD (MySQL analog function FIELD)

# Installation

```
git clone https://github.com/olegpro/sphinx-udf-field.git
cd sphinx-udf-field
make
sudo make install
```

Ensure that `sphinx.conf` contains plugin dir path:
```
common
{
	plugin_dir = /usr/local/sphinx/lib
}
```

# Register plugin

```
mysql -h127.0.0.1 -P9306

mysql> CREATE FUNCTION bk_field RETURNS BIGINT SONAME 'bk_field.so';
Query OK, 0 rows affected (0,00 sec)
```

# Usage

```
mysql -h127.0.0.1 -P9306

mysql> SELECT BK_FIELD('c', 'a', 'b', 'c', 'd', 'e');
+----------------------------------------+
| BK_FIELD('c', 'a', 'b', 'c', 'd', 'e') |
+----------------------------------------+
| 3                                      |
+----------------------------------------+
1 row in set (0.00 sec)
```

Blog post https://www.olegpro.ru/post/napisal_analog_funkcii_field_v_mysql_dlya_sphinx.html