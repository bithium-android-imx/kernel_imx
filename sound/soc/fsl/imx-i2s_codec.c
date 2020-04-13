/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 * Copyright 2012 Linaro Ltd.
 * Copyright 2020 Bithium S.A. All Rights Reserved.
 *
 * The code contained herein is licensed under the GNU General Public
 * License. You may obtain a copy of the GNU General Public License
 * Version 2 or later at the following locations:
 *
 * http://www.opensource.org/licenses/gpl-license.html
 * http://www.gnu.org/copyleft/gpl.html
 */

#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/clk.h>
#include <sound/soc.h>

#include "imx-audmux.h"

#define DAI_NAME_SIZE	32

struct imx_i2s_codec_data {
	struct snd_soc_dai_link dai;
	struct snd_soc_card card;
	char codec_dai_name[DAI_NAME_SIZE];
	char platform_name[DAI_NAME_SIZE];
};

static const struct snd_soc_dapm_widget imx_i2s_codec_dapm_widgets[] = {
	SND_SOC_DAPM_LINE("Line In Jack", NULL),
	SND_SOC_DAPM_SPK("Line Out Jack", NULL),
};

static int imx_i2s_codec_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device_node *ssi_np, *codec_np;
	struct platform_device *ssi_pdev;
	struct imx_i2s_codec_data *data = NULL;
	int int_port, ext_port;
	int ret;

	dev_info(&pdev->dev, "imx-i2s_codec probe start\n");

	ssi_np = of_parse_phandle(pdev->dev.of_node, "ssi-controller", 0);
	codec_np = of_parse_phandle(pdev->dev.of_node, "audio-codec", 0);
	if (!ssi_np || !codec_np) {
		dev_err(&pdev->dev, "phandle missing or invalid\n");
		ret = -EINVAL;
		goto fail;
	}

	ssi_pdev = of_find_device_by_node(ssi_np);
	if (!ssi_pdev) {
		dev_err(&pdev->dev, "failed to find SSI platform device\n");
		ret = -EPROBE_DEFER;
		goto fail;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data) {
		ret = -ENOMEM;
		goto fail;
	}

	data->dai.name = "HiFi";
	data->dai.stream_name = "HiFi";
	data->dai.codec_dai_name = "i2s_codec";
	data->dai.codec_of_node = codec_np;
	data->dai.cpu_of_node = ssi_np;
	data->dai.platform_of_node = ssi_np;
	data->dai.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			    SND_SOC_DAIFMT_CBM_CFM;

	data->card.dev = &pdev->dev;
	ret = snd_soc_of_parse_card_name(&data->card, "model");
	if (ret)
		goto fail;

	data->card.num_links = 1;
	data->card.owner = THIS_MODULE;
	data->card.dai_link = &data->dai;
	data->card.dapm_widgets = imx_i2s_codec_dapm_widgets;
	data->card.num_dapm_widgets = ARRAY_SIZE(imx_i2s_codec_dapm_widgets);

	platform_set_drvdata(pdev, &data->card);
	snd_soc_card_set_drvdata(&data->card, data);

	dev_info(&pdev->dev, "imx-i2s_codec probe register card\n");
	ret = devm_snd_soc_register_card(&pdev->dev, &data->card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
		goto fail;
	}

	of_node_put(ssi_np);
	of_node_put(codec_np);

	dev_info(&pdev->dev, "imx-i2s_codec exit ok\n");
	return 0;

fail:
	of_node_put(ssi_np);
	of_node_put(codec_np);

	dev_info(&pdev->dev, "imx-i2s_codec exit %x\n", ret);
	return ret;
}

static int imx_i2s_codec_remove(struct platform_device *pdev)
{
	return 0;
}

static const struct of_device_id imx_i2s_codec_dt_ids[] = {
	{ .compatible = "fsl,imx-audio-i2s_codec", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, imx_i2s_codec_dt_ids);

static struct platform_driver imx_i2s_codec_driver = {
	.driver = {
		.name = "imx-i2s_codec",
		.pm = &snd_soc_pm_ops,
		.of_match_table = imx_i2s_codec_dt_ids,
	},
	.probe = imx_i2s_codec_probe,
	.remove = imx_i2s_codec_remove,
};
module_platform_driver(imx_i2s_codec_driver);

MODULE_AUTHOR("Alexandre Sousa <alexandre.sousa@bithium.com>");
MODULE_DESCRIPTION("Generic I2S ASoC machine driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:imx-i2s_codec");
