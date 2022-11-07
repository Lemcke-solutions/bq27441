import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, sensor, text_sensor
from esphome.const import (
    CONF_ID,
    ICON_RADIATOR,
    ICON_RESTART,
    STATE_CLASS_MEASUREMENT,
    CONF_BASELINE,
    CONF_VERSION,
    CONF_BATTERY_LEVEL,
    UNIT_PERCENT,
    ICON_BATTERY,
    DEVICE_CLASS_BATTERY,
    STATE_CLASS_MEASUREMENT
)

AUTO_LOAD = ["text_sensor"]
CODEOWNERS = ["@lemckesolutions"]
DEPENDENCIES = ["i2c"]
CONF_BATTERY_CAPACITY = 'Battery capacity'

bq27441_ns = cg.esphome_ns.namespace("bq27441")
bq27441Component = bq27441_ns.class_(
    "BQ27441Component", cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(bq27441Component),
            cv.Required(CONF_BATTERY_LEVEL): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                icon=ICON_BATTERY,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_BATTERY,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Required(CONF_BATTERY_CAPACITY): cv.positive_int
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(i2c.i2c_device_schema(0x55))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    sens = await sensor.new_sensor(config[CONF_BATTERY_LEVEL])
    cg.add(var.set_battery_level(sens))

    if CONF_VERSION in config:
        sens = await text_sensor.new_text_sensor(config[CONF_VERSION])
        cg.add(var.set_version(sens))

    sens = await cg.get_variable(config[CONF_BATTERY_CAPACITY])
    cg.add(var.set_battery_capacity(sens))
