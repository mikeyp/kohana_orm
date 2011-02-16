<?php
// $Id$

class DatabaseConnection_base_kohana {

  public $_db_connection;

  public function __call($method, $args) {
    $return = call_user_func_array(array($this->_db_connection, $method), $args);

    // Some methods will return the called object as part of a fluent interface.
    // Others will return some useful value.  If it's a value, then the caller
    // probably wants that value.  If it's the called object, then we instead
    // return this object.  That way we don't "lose" an extender layer when
    // chaining methods together.
    if ($return instanceof PDO) {
      return $this;
    }
    else {
      return $return;
    }
  }

  protected function _parse_type($type) {
    if (($open = strpos($type, '(')) === FALSE) {
      // No length specified
      return array($type, NULL);
    }

    // Closing parenthesis
    $close = strpos($type, ')', $open);

    // Length without parentheses
    $length = substr($type, $open + 1, $close - 1 - $open);

    // Type without the length
    $type = substr($type, 0, $open).substr($type, $close + 1);

    return array($type, $length);
  }

  public function datatype($type) {
    static $types = array(
      // SQL-92
      'bit'                           => array('type' => 'string', 'exact' => TRUE),
      'bit varying'                   => array('type' => 'string'),
      'char'                          => array('type' => 'string', 'exact' => TRUE),
      'char varying'                  => array('type' => 'string'),
      'character'                     => array('type' => 'string', 'exact' => TRUE),
      'character varying'             => array('type' => 'string'),
      'date'                          => array('type' => 'string'),
      'dec'                           => array('type' => 'float', 'exact' => TRUE),
      'decimal'                       => array('type' => 'float', 'exact' => TRUE),
      'double precision'              => array('type' => 'float'),
      'float'                         => array('type' => 'float'),
      'int'                           => array('type' => 'int', 'min' => '-2147483648', 'max' => '2147483647'),
      'integer'                       => array('type' => 'int', 'min' => '-2147483648', 'max' => '2147483647'),
      'interval'                      => array('type' => 'string'),
      'national char'                 => array('type' => 'string', 'exact' => TRUE),
      'national char varying'         => array('type' => 'string'),
      'national character'            => array('type' => 'string', 'exact' => TRUE),
      'national character varying'    => array('type' => 'string'),
      'nchar'                         => array('type' => 'string', 'exact' => TRUE),
      'nchar varying'                 => array('type' => 'string'),
      'numeric'                       => array('type' => 'float', 'exact' => TRUE),
      'real'                          => array('type' => 'float'),
      'smallint'                      => array('type' => 'int', 'min' => '-32768', 'max' => '32767'),
      'time'                          => array('type' => 'string'),
      'time with time zone'           => array('type' => 'string'),
      'timestamp'                     => array('type' => 'string'),
      'timestamp with time zone'      => array('type' => 'string'),
      'varchar'                       => array('type' => 'string'),

      // SQL:1999
      'binary large object'               => array('type' => 'string', 'binary' => TRUE),
      'blob'                              => array('type' => 'string', 'binary' => TRUE),
      'boolean'                           => array('type' => 'bool'),
      'char large object'                 => array('type' => 'string'),
      'character large object'            => array('type' => 'string'),
      'clob'                              => array('type' => 'string'),
      'national character large object'   => array('type' => 'string'),
      'nchar large object'                => array('type' => 'string'),
      'nclob'                             => array('type' => 'string'),
      'time without time zone'            => array('type' => 'string'),
      'timestamp without time zone'       => array('type' => 'string'),

      // SQL:2003
      'bigint'    => array('type' => 'int', 'min' => '-9223372036854775808', 'max' => '9223372036854775807'),

      // SQL:2008
      'binary'            => array('type' => 'string', 'binary' => TRUE, 'exact' => TRUE),
      'binary varying'    => array('type' => 'string', 'binary' => TRUE),
      'varbinary'         => array('type' => 'string', 'binary' => TRUE),
    );

    if (isset($types[$type]))
      return $types[$type];

    return array();
  }

}
